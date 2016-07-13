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
    a:setX(10)
    a:setY(20)
    test(a:getX())
    test(a:getY())
    a:setPosition(30,9)
    test(a:getX())
    test(a:getY())
end

testobject = function()
    object.setX(123)
    test(object.getX())
end

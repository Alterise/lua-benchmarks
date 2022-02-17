function increment2(x)
  return x + 1
end

function string_argument2(s1, s2)
  return s1:sub(-1, -1) .. s2:sub(-1, -1)
end

function string_iterator2(s1, s2, count)
  if count % 2 then
    return s1
  else
    return s2
  end
end

function pass_class2(a)

end

function get_class2()
  return A1
end
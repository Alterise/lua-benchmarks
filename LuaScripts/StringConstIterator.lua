nums = {'1', '12','123','1234','12345','123456','1234567','12345678','123456789','1234567890',
'12345678909','123456789098','1234567890987','12345678909876','123456789098765',
'1234567890987654','12345678909876543','123456789098765432', '1234567890987654321', '12345678909876543210'}
for i = 1, loop_count do
  string_const_iterator(nums[i % 20 + 1], nums[20 - i % 20], i)
end
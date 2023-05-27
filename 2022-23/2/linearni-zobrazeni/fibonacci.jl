function fibonacci(n)
  start = [0, 1]
  x = n
  log_2 = 0
  while x > 0
    x = x >> 1
    log_2 += 1
  end
  final_matrix = [1 0; 0 1]
  cur = [0 1; 1 1]
  if n % 2 == 1
    final_matrix = cur
  end
  for i in 2:log_2
    cur = cur * cur
    if (1 << (i - 1)) & n != 0
      final_matrix = final_matrix * cur
    end
  end

  return (final_matrix*start)[1]
end

# Read stdin and return fibonacci
println(fibonacci(parse(Int64, chomp(readline()))))

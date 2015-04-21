stone_n = input()
stones = map(int, raw_input().split())
sort_stones = sorted(stones)

op_stones = [0]
op_sort_stones = [0]
tmp_sum_1 = 0
tmp_sum_2 = 0

for i in xrange(stone_n):
	tmp_sum_1 += stones[i]
	tmp_sum_2 += sort_stones[i]
	op_stones.append(tmp_sum_1)
	op_sort_stones.append(tmp_sum_2)

question_n = input()
for i in xrange(question_n):
	q_type, l, r = map(int, raw_input().split())
	
	if q_type == 2:
		print op_sort_stones[r] - op_sort_stones[l-1]
	else:
		print op_stones[r] - op_stones[l-1]

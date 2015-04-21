n = input()
apples = map(int, raw_input().split())

one = apples.count(100)
two = n - one

if one%2==1 or (one==0 and two%2 == 1) or (one==0 and two==0):
	print 'NO'
else:
	print 'YES'

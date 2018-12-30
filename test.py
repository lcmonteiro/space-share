

a = "%saa%s"
b = ("aaaaaaaaaa", "bbbbbbbbbbbb")

c = a % tuple([ "s" for i in range(2)])

print(c)
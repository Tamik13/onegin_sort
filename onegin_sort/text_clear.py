inp = open("onegin.txt", encoding = "utf8")
out = open("clear_onegin.txt", mode = "w+", encoding = "ascii")

for i in inp:
    for j in i:
        if ord(j) < 128:
            out.write(j)

inp.close()
out.close()

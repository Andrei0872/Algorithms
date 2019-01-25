def increment_string(s):
    head = s.rstrip("0123456789")
    tail = s[len(head):]

    if tail == "": return s + 1
    return head + str(int(tail) + 1).zfill(len(tail))

strng = "foobar009"

print(increment_string(strng))
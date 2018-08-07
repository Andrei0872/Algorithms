
# Link to the task : https://www.codewars.com/kata/printer-errors
def printerError(s):
    return "{}/{}".format(len([x for x in s if x not in "abcdefghijklm"]),len(s))
print printerError("aaaxbbbbyyhwawiwjjjwwm") # 8/22


def printerError2(s):
    return "{}/{}".format(len(s.translate(None,"abcdefghijklm")),len(s)) 
print printerError2("aaaxbbbbyyhwawiwjjjwwm") # 8/22


from re import sub
def printerError3(s):
    return "{}/{}".format(len(sub("[a-m]",'',s)),len(s))
print printerError3("aaaxbbbbyyhwawiwjjjwwm") # 8/22

import string

def rot13 (message):
    input_ = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'
    output_ = 'NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm'

    return message.translate(string.maketrans(input_, output_))

print(rot13("test")) # grfg

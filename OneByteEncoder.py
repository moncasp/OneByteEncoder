import sys, optparse


parse_ob = optparse.OptionParser()

def get_input():
    parse_ob.add_option("-e", "--encode", dest="encodeFile", type="string", help="file to be encrypted")
    parse_ob.add_option("-d", "--decode", dest="decodeFile", type="string", help="file to be decrypted")
    parse_ob.add_option("-k", "--key", dest="key", type="int", help="first key")

def oneByteEncoder(sourceFile, key):
    with open(sourceFile, "rb") as file:
        data = file.read()
    with open("oneByteEncoder.output", "wb") as file:
        for i in data:
            deger = key ^ i
            aa = hex(deger)
            if len(aa) == 3:
                deger = "0x0" + aa[2]
            elif len(aa) == 4:
                deger = aa
            else:
                print("Beklenemyen Hata Oluştu\n")
                break
            key = int(deger, 0)
            file.write(bytearray.fromhex(deger.replace("0x", "")))


def oneByteDecoder(decodeFile,key):
    with open(decodeFile, "rb") as file:
        data = file.read()
    with open("oneByteEncoder.output", "wb") as file:
        for i in data:
            deger = i
            aa = hex(key ^ i)
            if len(aa) == 3:
                decod = "0x0" + aa[2]
            elif len(aa) == 4:
                decod = aa
            else:
                print("Bir Hata İle karşılaşıldı")
                break
            key= deger
            file.write(bytearray.fromhex(decod.replace("0x", "")))

if __name__ == "__main__":
    print("\nAuthor: https://github.com/moncasp \n\n")
    get_input()
    user, a = parse_ob.parse_args()
    if user.encodeFile != None and user.decodeFile != None:
        print("The -e and -d parameters cannot be used together")
    elif user.encodeFile == None and user.decodeFile == None:
        print("Use one of the -e and -d parameters")
    elif user.key == None:
        print("enter a key")
    else:
        if user.encodeFile !=None:
            print("One Byte Encoder Started....")
            oneByteEncoder(user.encodeFile,user.key)
            print("One Byte Encoder Is Over")
        else:
            print("One Byte Decoder Started....")
            oneByteDecoder(user.decodeFile,user.key)
            print("One Byte Decoder Is Over")




import sys

def main():
    sentence = ""
    nextNew = 1
    # for line in sys.stdin:
    while True:
        line = input()
        if line == "-1":
            break
        if len(line) != 0:
            if nextNew == 1:
                sentence += line.lower()
                nextNew = -1
            else:
                sentence += line.lower().title()
        else:
            sentence += " "
            nextNew = 1
  
    print(sentence)

if __name__ == "__main__":
    main()

# Camel
# Case
# 
# LOOKS
# like
# ThIs

# Output: camelCase looksLikeThis

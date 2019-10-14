def main():
  String1 = input()
  String2 = input()
  print(isAnagram(String1.lower(), String2.lower()))

def isAnagram(String1, String2):
  alpha = "abcdefghijklmnopqrstuvwxyz"
  if len(String1) != len(String2):
    return False
  for c in alpha:
    if String1.count(c) != String2.count(c):
      return False
  return True

main()
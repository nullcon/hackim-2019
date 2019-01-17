import ebcdic
import sys
import difflib

def ed(enc,dec):
 id="!@~`#$%^*&()_-=+|\]}[{'\";:?/>.<,"
 ency=id.encode(enc)
 decy=ency.decode(dec)
 
 print "ID"
 print id 
 print "Encrypted"
 print ency
 print "decrypted"
 print decy
 
 for i,s in enumerate(difflib.ndiff(id, decy)):
   if s[0]==' ': continue
   elif s[0]=='-':
      print(u'Delete "{}" from position {}'.format(s[-1],i))
   elif s[0]=='+':
      print(u'Add "{}" to position {}'.format(s[-1],i))    
 print()      

 

ed(sys.argv[1],sys.argv[2])
 

# Interpreter for Scheme 的介紹：

0. I've got interested in this program, how can I start to implement ?  

    我已經將這隻程式所依循的原始文件 upload , 關於這隻程式所有的 details, 你都可以在這兩份文件內找到。  

1. what is Scheme ?

    Scheme is a programming language. Is a kind of LISP.
    This is Scheme intruduction in the wiki : https://zh.wikipedia.org/wiki/Scheme  

2. what it can do / or 這程式可以做到什麼樣的一個地步？

    input 一段標準的 Scheme 指令，  
    （ even including some comments, moreover your commands cross line. My program can handle !! ），  
    這個程式會將 commands 切成 token, 會去檢查 commands 是否符合 Scheme 的文法，  
    如果文法有錯，我的程式可以告知你，在什麼地方發生錯誤，  
    如果合乎文法，我的程式會將 commands 做運算，給出 commands 在正常情況下該有的 output.  
  
  
3. About syntax and commands :

    如果你想更好的了解這個程式，或者是說你想對 scheme 指令有初步的了解，  
    非常歡迎您點開 folder 裡面的 Syntax, Implement commands ,  
    在這裡面介紹了這隻程式所遵循的文法和一些被 implement 的指令。


# I've prepared some commands can quickly demo

    Before you see these commands I hope you know,  
    there only exists 3 kinds of commands,
    
    first,  start with ATOM and only ATOM ,  
      
    second, start with '(' and go on arguments then end up with ')' ,   
    ex : ( arguments arguments )  
    Note : most of the functions I implement, follow this type.  
    
      
    third,  start with '   and go on arguments.  
    ex : 'arguments
    
    the basic commands will be like :
    
    ( + 1245 53 )  
    ( cons 6 5555 )  
    ( list 5675 + )  
      
    ( define a + )  
    ( a 132 456 ) // after define a as plus, a become new operator here.  
    
    
# QA Session :

1. 為什麼我在按下 enter 以後，程式沒有反應？

    會出現這種情況，只有一種可能，截至 enter 為止，你的command 都合乎文法，  
    但是程式並沒有等到預期的結尾，所以這段 command 並認定為尚未 key 完的 command，  
    那因為有支援 cross line command，所以你只要把預期的結尾補足，相信就能看到 output.


    
    

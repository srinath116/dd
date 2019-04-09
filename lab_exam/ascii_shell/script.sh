
echo please enter a char to know its asciivalue:
read message
AscValue=`printf "%d" "'$message'"`
echo input: ${message} 
echo asciivalue :${AscValue}


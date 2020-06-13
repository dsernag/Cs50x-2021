from cs50 import get_string
######################    
#Def main function
######################    
def main():
    s = get_string("Text: ")
    words = s.split()

    count_letters = 0 #To count letters
    count_sentences = 0 #To count sentences
    word = len(words) #Number of words
    count = 0 #Number to count special characters 

    for words in s:
        if words == "." or words == "!" or words == "?":
            count_sentences += 1
        elif words == "'" or words == " ":
            count += 1
        else:
            count_letters += 1
    L = (count_letters * 100) / word 
    S = (count_sentences *100) / word
    
    index = round((0.0588 * L) - (0.296 * S) - 15.8)
    
    if index >= 16:
        print("Grade 16+")
    elif index <= 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")
######################

main()

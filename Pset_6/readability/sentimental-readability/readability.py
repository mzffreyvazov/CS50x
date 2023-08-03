def calc_readability(text):
    # index = 0.0588 * l - 0.296 * s - 15.8
    # L is average number of letters per 100 words.
    # S is average number of sentences per 100 words.

    number_of_words = 0
    number_of_letters = 0
    number_of_sentences = 0
    l = s = 0
    sentence_end_symbols = ['.', '!', '?']
    other_symbols = [',', ';', ':', '-', '(', ')', '[', ']', '{', '}', '@', '#', '$', '%',
    '^', '&', '*', '+', '=', '<', '>', '/', '|', '\\', '`', '~', " ", "?", '.', '!', '?', "'"]
    for i in text:
        if i in sentence_end_symbols:
            number_of_sentences += 1
        if i not in other_symbols:
            number_of_letters += 1
        if i == " ":
            number_of_words += 1


    number_of_words += 1
    l = (number_of_letters / number_of_words) * 100
    s = (number_of_sentences / number_of_words) * 100
    index = 0.0588 * l - 0.296 * s - 15.8

    return (number_of_sentences, number_of_letters, number_of_words, round(index))




if __name__ == "__main__":
    text = input("Text: ")
    sentence, letters, words, index = calc_readability(text)
    if index <= 0:
        index = "Before Grade 1"
    elif index >+ 16:
        index = '16+'

    print("Grade", index)

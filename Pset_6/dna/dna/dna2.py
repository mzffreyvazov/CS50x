import csv
import sys

def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If not, break out of the loop to avoid overcounting
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


def main():

    # Check for correct number of command-line arguments
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # Read database file into a variable
    with open(sys.argv[1]) as csvfile:
        reader = csv.DictReader(csvfile)
        dna_db = [person for person in reader]
        header = reader.fieldnames[1:] # save STR sequence header names

    # Read DNA sequence file into a variable
    with open(sys.argv[2]) as txtfile:
        dna_seq = txtfile.read()

    # Compute longest run of each STR in DNA sequence
    dna_data = [longest_match(dna_seq, seq) for seq in header]

    # Check if STR counts match to any person's DNA
    for person in dna_db:
        match = True
        for i in range(len(header)):
            if int(person[header[i]]) != dna_data[i]:
                match = False
                break
        if match:
            print(person['name'])
            return

    # If no match, print "No match"
    print("No match")

main()





import csv
import sys


def main():

    # TODO: Check for command-line usage

    # TODO: Read database file into a variable

    # TODO: Read DNA sequence file into a variable

    # TODO: Find longest match of each STR in DNA sequence

    # TODO: Check database for matching profiles

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
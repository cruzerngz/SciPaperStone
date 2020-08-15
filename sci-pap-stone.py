#Import libraries
import random, time
#List of variables
inputattempt = 0 
choicelist = ["scissors","paper","stone"]
#added more than 1 choice of input
choice1 = "Scissors_scissors_1"
choice2 = "Paper_paper_2"
choice3 = "Stone_stone_3"
#Change the number of rounds below
prescribed_rounds = 3
#Change the number of invalid entries below
prescribed_attempts = 5
#At the start point of the game all counters are set to 0
roundcount = 0
userwins = 0
comwins = 0

#Checks that input is an integer, re-prompts if it isn't 
#Hash out the function in line 48 if you do not want it inside the game
def keyboard_input():
    try:
        prescribed_rounds = int(input("Choose the number of games to play: "))
    except:
        print("Please enter a whole number.\n")
        keyboard_input()

#End of game statements
#Moved this chunk up here so that game can be ended anytime though the end command
def end_game():
    time.sleep(0.5)
    if userwins < comwins:
        print("You lose this game!\nThanks for playing!")
    elif comwins < userwins:
        print("You win this game!\nThanks for playing!")
    else:
        print("This game is a draw!\nThanks for playing!")
    time.sleep(0.5)
    input("press enter to exit...")
    exit()

#Game introduction
print("Welcome to scissors paper stone!")
time.sleep(0.5)

#Hash out the line below if you don't want the user to choose the number of games
keyboard_input()

time.sleep(0.5)
print("This is a best of " + str(prescribed_rounds) + "!\n")
time.sleep(0.5)

while roundcount < prescribed_rounds:
    while inputattempt < prescribed_attempts:
        ##Get the user's play
        userinput = input("Turn " + str(roundcount + 1) + "/" + str(prescribed_rounds) + "\nChoose your [scissors,paper,stone]!\n")
        #Check for any errors in selection, then proceeds with game if true
        #Now accepts shortform of the full word, as well as numbers corresponding to the position in list
        if userinput in choice1 + choice2 + choice3:
            print("you have chosen " + userinput + "!")
            #resets number of false attempts back to 0 for more shenanigans
            inputattempt = 0
            break
        elif userinput in ["End","end","Finish","finish","Stop","stop","Exit","exit"]:
            end_game()
        #Prints out a random string from the list below, and prompts a re-entry
        else:
            insultlist = ["Um... I am out of words.","How are you so bad at this?","Don't play games with me","We're playing scissors paper stone here","what are you doing?","as a computer I can't believe I'm facepalming","do you know how the world works?","Do you know how to type?"]
            #added a self counting system so insults can be added any time
            insultcount = len(insultlist)
            insultindex = random.randint(0,insultcount - 1)
            print(insultlist[insultindex])
            #Adds to the current count of unsuccessful attempts
            inputattempt += 1
            time.sleep(0.5)
            #The number of tries can be modified to any amount necessary
            #To change the no. of tries, modify the prescribed_attempts variable
            if inputattempt < prescribed_attempts - 1:
                remainingtry = prescribed_attempts - inputattempt
                print("You have " + str(remainingtry) + " tries left!\n")
            #accounted for the grammatical error "1 tries" -> "1 try" below
            elif inputattempt == prescribed_attempts - 1:
                remainingtry = prescribed_attempts - inputattempt
                print("You have " + str(remainingtry) + " try left!\n")
            #The last condition will exit the game
            elif inputattempt == prescribed_attempts:
                print("Unsuccessfully entered " + str(inputattempt) + " times.")
                input("press enter to exit...")
                exit()
            
    ##Get the computer's play
    comchoiceno = random.randint(0,2)
    time.sleep(1)
    print("The computer chooses " + str(choicelist[comchoiceno]) + "!")
    #Game pauses 1 second for dramatic effect
    time.sleep(1)
    #As a best of style of game, the loop will keep going until the number of games hits the prescribed amount
    while comchoiceno == 0:
        roundcount += 1
        if userinput in choice1:
            print("It's a draw!")
        elif userinput in choice2:
            print("You lose!")
            comwins += 1
        elif userinput in choice3:
            print("You win!")
            userwins += 1
        print("computer: " + str(comwins) + ", you: " + str(userwins) + "\n")
        break

    while comchoiceno == 1:
        roundcount += 1
        if userinput in choice1:
            print("You win!")
            userwins += 1
        elif userinput in choice2:
            print("It's a draw!")
        elif userinput in choice3:
            print("You lose!")
            comwins += 1
        print("computer: " + str(comwins) + ", you: " + str(userwins) + "\n")
        break

    while comchoiceno == 2:
        roundcount += 1
        if userinput in choice1:
            print("You lose!")
            comwins += 1
        elif userinput in choice2:
            print("You win!")
            userwins += 1
        elif userinput in choice3:
            print("It's a draw!")
        print("computer: " + str(comwins) + ", you: " + str(userwins) + "\n")
        break
    
    #This checks the number of remaining turns with the score gap between player and computer.
    #Game ends when the score gap cannot be closed.
    if abs(userwins - comwins) > prescribed_rounds - roundcount:
        break
    else:
        continue

#End of game statements
end_game()

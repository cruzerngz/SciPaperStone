#Import libraries
import random, time

#List of variables
inputattempt = 0 
choicelist = ["scissors","paper","stone"]
#added more than 1 choice of input
choice1 = "Scissors scissors 1"
choice2 = "Paper paper 2"
choice3 = "Stone stone 3"
#Change the number of games below
prescribed_games = 3
#Change the number of invalid entries below
prescribed_attempts = 5
#At the start point of the game all counters are set to 0
gamecount = 0
userwins = 0
comwins = 0

print("Welcome to scissors paper stone!")
time.sleep(0.5)

#Checks that input is an integer, exits the code if it isn't
#Hash out the next 6 lines if you do not want the user to change no. of games
try:
    prescribed_games = int(input("Choose the number of games to play:\n"))
except:
    print("error. not a number")
    input("press enter to exit...")
    exit()

time.sleep(0.5)
print("This is a best of " + str(prescribed_games) + "!\n")
time.sleep(0.5)

while gamecount < prescribed_games:
    while inputattempt < prescribed_attempts:
        ##Get the user's play
        userinput = input("Turn " + str(gamecount + 1) + "\nChoose your [scissors,paper,stone]!\n")
        #Check for any errors in selection, then proceeds with game if true
        if userinput in choice1 + choice2 + choice3:
            print("you have chosen " + userinput + "!")
            #resets number of false attempts back to 0 for more shenanigans
            inputattempt = 0
            break
        
        #Prints out a random string from the list below, and prompts a re-entry
        else:
            insultlist = ["Don't play games with me","We're playing scissors paper stone here","what are you doing?","as a computer I can't believe I'm facepalming","do you know how the world works?","Do you know how to type?"]
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
        gamecount += 1
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
        gamecount += 1
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
        gamecount += 1
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
    if abs(userwins - comwins) > prescribed_games - gamecount:
        break
    else:
        continue 

#End of game statements
time.sleep(0.5)
if userwins < comwins:
    print("You lose this game!\nThanks for playing!")
elif comwins < userwins:
    print("You win this game!\nThanks for playing!")
else:
    print("This game is a draw!\nThanks for playing!")
time.sleep(0.5)
input("press enter to exit...")

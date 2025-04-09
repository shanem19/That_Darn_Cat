#include <iostream>
//SFML(simple and fast multimedia library) this sucker is litterally used to make games

#include <SFML/Graphics.hpp> //this is for adding and using the imagaes of my cat
#include <SFML/Audio.hpp> // this allows me to manipulate audio files and use them
//#include <vector>// I have 2 vectors , one  my random meowing sounds and the other for my random delay times


#include "../../../../Library/Developer/CommandLineTools/SDKs/MacOSX13.1.sdk/System/Library/Frameworks/CoreGraphics.framework/Headers/CGColor.h"//this just popped up out of nowhere lol but I belive this is helping my mac work with the sfmls graphics module

using namespace sf;// sf is what is used for sfml. so I dont have to type sf:: over and over
using namespace std;// for me standard


int main() {
    //as you can see by my project name was going to be damn cat, but my wife was like you should call it that darn cat because it sounds better lol

    // creating my game window
    //Render window uses the class window and creates a window object, game screen is the name I gave my window object
    //to set up all the settings of my window I have to call the function videomode which lets you set width,height, and a title
    //I chose 2000 X 2000 because I wanted it to be a decent size and if both sides of the screen is even it makes my life easier
    RenderWindow game_screen(VideoMode(2000, 2000), "That Darn Cat!");

    //********* AUDIO ********\\

//so I spent about a good 2 hours chasing my cat around the house trying to record him making his normal cat sounds
// I used voice memos app on my iphone, then I airdropped them to my apple music, after that I changed their formating to
// wav files. for sfml.audio, it really only likes wav,og,and I think mp3 files?

//originally i wanted to use a sound class for the purring
// but it wouldnt work, so I made the wav file of proffessor purring music
// the main difference between music and sound is that music is opened directly from the source

  Music professor_purring;//making a Music object
  professor_purring.openFromFile("/Users/shanemeldrim/CLionProjects/Damn_Cat/professor purring.wav");//opening from file using a direct path
    professor_purring.setVolume(100);// I thought this would make his purring louder but it did nothing
    professor_purring.setLoop(true);// setting an endless loop so he will pur the whole game
    professor_purring.play();//here im actually starting the playing of his purring



//sounds

//for sounds to be used , first you have to create a soundBuffer
// SoundBuffers are classes that store audio samples.
    SoundBuffer professor_stop;//here I am making a object named professor stop
    professor_stop.loadFromFile("/Users/shanemeldrim/CLionProjects/Damn_Cat/professor_stop.wav");// now im doing a method which is actually loadinging the file which is a array of samples and storing it into my object
//a Sound class is what actually lets us manage the audio samples
    Sound Professor_stop;// here im creating my sound object
    Professor_stop.setBuffer(professor_stop);// here im refrencing this buffer. so now if i were to do Professor_stop.play() it will play the audio data stored at professor_stop

    SoundBuffer meow_short;
    meow_short.loadFromFile("/Users/shanemeldrim/CLionProjects/Damn_Cat/Professor meowing edited short.wav");
    Sound Meow_short;
    Meow_short.setBuffer(meow_short);

    SoundBuffer sassy_meow;
    sassy_meow.loadFromFile("/Users/shanemeldrim/CLionProjects/Damn_Cat/sassy pur.wav");
    Sound Sassy_meow;
    Sassy_meow.setBuffer(sassy_meow);


//here im making a vector to store my meow sounds so I can randomly play them while the window is open
    vector<Sound> random_meows = {Sassy_meow,Meow_short};
    int meows_random_index;

    //***** TEXT ******\\

//Text is a part of the graphics module of sfml

    Font font;//font is a class that allows you to load and manipalate different fonts
    //this took me forever, I had to find a font from google fonts, then download it
    // because you kinda have to find a font and download it to use with sfml graphics
    font.loadFromFile("/Users/shanemeldrim/CLionProjects/Damn_Cat/Barriecito-Regular.ttf");
    Text game_over_text;// text class reffrences font and allows you to draw on a target
    game_over_text.setFont(font);//here im renfrencing to the Fonct class font
    game_over_text.setString("Meow meow meow!\nMeow Meow.....Meow Meow\nMeow meow meow?"
                             );
    game_over_text.setCharacterSize(80);// controling how big my letters are
    game_over_text.setFillColor((Color::Cyan));// I think you can get away with typing in rgb values?
    game_over_text.setPosition(1100,700);//choosing the coordinates of where I want to put my words




    //********IMAGES/SPRITES***********\\

// A texture is literally a image that is saved within a computers graphics card that
// can be used for drawing on the screen.
// first I have to make a Texture object
// then I Load it to that object by using its classes public function Loadfromfile
// to actually use the texture I refrence it through the Sprite class
// The main reason why its done like that is because texture uses alot and is a "heavy" resorce
// sprites dont use much and they can draw the texture faster without using too much data
//sprites can also manipulate size, color, rotation because it inherants from the drawable and transformable classes

    // loading in all my images and turning them into sprites and scaling them to size
    Texture background;
    background.loadFromFile("/Users/shanemeldrim/CLionProjects/Damn_Cat/game_background.jpg");
    Sprite back_ground;
    back_ground.setTexture(background);
    back_ground.setScale(1.5, 1);

    // this is my cat professor my phone lets me turn his picture into a png which will only show just him
    Texture cat;
    cat.loadFromFile("/Users/shanemeldrim/CLionProjects/Damn_Cat/professor_mycat.png");
    Sprite Cat;
    Cat.setTexture(cat);
    Cat.setScale(0.27f, 0.27f);
    Cat.setPosition(650, 100);

    // I had to separate my cat's paw so I could give it independent movement
    Texture cat_paw;
    cat_paw.loadFromFile("/Users/shanemeldrim/CLionProjects/Damn_Cat/cat_paw.png");
    Sprite Cat_paw;
    Cat_paw.setTexture(cat_paw);
    Cat_paw.setScale(0.27f, 0.27f);
    Cat_paw.setPosition(850, 700);

    // I took a picture of a cup in my house and brought it all in
    Texture cup;
    cup.loadFromFile("/Users/shanemeldrim/CLionProjects/Damn_Cat/cup.png");
    Sprite Cup;
    Cup.setTexture(cup);
    Cup.setScale(0.20f, 0.20f);
    Cup.setPosition(810, 700);

    //******* MOVEMENT **********\\
//in this game there is only two things I want to move
// my cats paw, and the glass of water
// since my cups movement is reactive to my cats paw movement,
// its movement logic will be in the actuall game loop


    // my cats paw speed
    //float normal_speed = 6.0;//how fast professors paw will rotate at the start of game
    //float paw_rotationSpeed = normal_speed; // positive it goes clockwise, negative counter clockwise
    float rotationspeeds[] = {1,3,6,7};//here im making a array of speeds that a can randomly chose from
    int element_amount_for_speed = sizeof(rotationspeeds) / sizeof(rotationspeeds[0]);// all this is doing is dividing the amount of bits used to make my array by the size of my data type which shows the amount of elements for my randomizer to pick from
    int  speed_random_index;

    float paw_rotationSpeed = 6;// i tried something different and i didnt like it
    float transition_speed = 2;        // Rate of transition (how quickly the speed changes)

    // stuff for the paws rotation
    float paw_currentRotation = 0.0;// gives a status of where the paw is rotated
    bool cat_paw_rotatingLeft = true; // Flag to control paw rotation


    // ***** TIME ******//
    // all games require a clock , clocks maintain time elapsed and you can controll alot using a clock
    Clock clock;// clock for game
    Clock meow_clock;//clock for when professor meows
    float time_to_meow=2.78;// at what amount of ellapsed time professor will meow
// here to spice things Up i wanted to randomize when professors paw would start
// to move after the user hits the space bar
//so just like how I made my random rotation speeds I created array for random delay times
    float delay_times[] = {.7,.8,.9,1};
    int amount_of_elements_for_delay_times = sizeof(delay_times) / sizeof(delay_times[0]);
    int  delay_times_random_index;
    //********* GAME LOOP *********//

    //all games work the same in one aspect
    //all games are literally a endless loop that have events
    //every game needs a close event or else the window will remain open forever
    // it also needs key or mouse events so the user can interact with the game.
    // but within this loop is where all the work happens

    // this while statement is what creates the game loop
    // basically its saying while(true)
    while (game_screen.isOpen()) {
        Event event;// this class defines a system event and its parameters. so basically it contains info on the mouse,keys,trackpad

   //the method pollEvent is looking to see if the user has pressed any key or clicked something with the mouse
   // in this instant we will constantly be looking at user inputs
   // and if we see that they have clicked the x button on the windows top left
   //we will close my game window
        while (game_screen.pollEvent(event)) {
            if (event.type == Event::Closed) game_screen.close();
        }

    // here as the window opens our meow clock is going to start to tick
    // this if statement is saying if the amount of time is elapsed is greater than
    // or equal to the time i have set to my variable time to meow
    // also i wanted to explain how rand is working in this situation
    //rand is a function that will return a pseudo_random number
    // the modulus followed by a number will give rand a range of numbers to select from
    // since the amount of elements in my vector are 2 rand will select between numbers 0 and 1
    // now I will play the meow sound either in index 0 or index 1
    // after that the clock resets and continues to count
        if (meow_clock.getElapsedTime().asSeconds() >= time_to_meow) {
             meows_random_index = rand()%random_meows.size();
            random_meows[meows_random_index].play();
            meow_clock.restart();
        }

// right here is my 2nd and last input for this game
// here im saying "i want you to look at the keyboard. did they push the space key?"
// if they did , I want you to stop the paw from moving, play the sound professor stop, delay the game for a certian amout
// of seconds , then move the paw again.
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            // When space is pressed, stop the paw rotation for a short moment
             Professor_stop.play();
            //cat_paw_rotatingLeft = false;// not necessary

            // Randomly select a delay time
            delay_times_random_index = rand() % amount_of_elements_for_delay_times;
            float delayseconds = delay_times[delay_times_random_index];


               cat_paw_rotatingLeft=false;

            while (clock.getElapsedTime().asSeconds() < delayseconds) {
            }
            if (clock.getElapsedTime().asSeconds()==delayseconds) {
                cat_paw_rotatingLeft = true;
            }





            //cat_paw_rotatingLeft = true; // not necesarry

            // Randomly select a rotation speed from the array
            speed_random_index = rand() % element_amount_for_speed;
            int target_speed = rotationspeeds[speed_random_index];

        // Smoothly transition the rotation speed towards the target speed
        // at first my speed would be to fast after space was hit so you really had like no
        //chances to hit space and the cup would just jump
        // for this part I looked up what to do and this basically is making the changes from the random speeds slightly more
        //gradual so the cup wouldnt just jump off the table
            //cat_paw_rotatingLeft = true;

        if (cat_paw_rotatingLeft) {
            if (paw_rotationSpeed < target_speed) {
                paw_rotationSpeed += transition_speed;  // Gradually increase the speed
                if (paw_rotationSpeed > target_speed) paw_rotationSpeed = target_speed;  // Clamp the speed
            }
            else if (paw_rotationSpeed > target_speed) {
                paw_rotationSpeed -= transition_speed;  // Gradually decrease the speed
                if (paw_rotationSpeed < target_speed) paw_rotationSpeed = target_speed;  // Clamp the speed
            }
        }
    }
        // Update the rotation of the cat's paw
        // here I wanted to leave a big note, while we are looking at paws rotation
        // we are looking at a value of degrees in a circle.
        float rotate_Time = clock.restart().asSeconds();

        if (cat_paw_rotatingLeft) {
            paw_currentRotation += paw_rotationSpeed * rotate_Time;  // this right here is what gives us smooth movement. as the clock ticks the paw will rotate left at a rate of  the paws rotation speed




// this guy below says if cat paws rect and cups rect intersect, I want you to move left with a slightly reduced speed

            if (Cat_paw.getGlobalBounds().intersects(Cup.getGlobalBounds())){
                    Cup.move(  -0.03*paw_rotationSpeed, 0.f);
// this makes it to where professors paw wont do a 360 and it makes the cup disapear.
                if (paw_currentRotation >= 75.5) {
                    Cup.move(0, 670);  // Move the cup down
                    cat_paw_rotatingLeft = false;  // Stop rotating when paw reaches a certain angle
                }
            }
        }
// this is the part of the game where I actually begining to draw my sprites,
// start my paws movement and update my window


        // Apply the rotation to the cat's paw
        Cat_paw.setRotation(paw_currentRotation);

        // Update the game window
        game_screen.clear();

        // Draw sprites
        game_screen.draw(back_ground);
        game_screen.draw(Cat);
        game_screen.draw(Cat_paw);
        game_screen.draw(Cup);

// this guy shows the user what has been drawn on the screen so far
        game_screen.display();


//these are my end game statements im simply adding the y value of where I draw the cup with the amount I make it move down
        // when prof pushes it off

        if (Cup.getPosition().y>=1370.f) {
    game_screen.clear();//it was a pain figuring this out, but I had to wipe my screen and redraw everything if i wanted my final text

    // I had to redraw my sprites without the cup
    game_screen.draw(back_ground);
    game_screen.draw(Cat);
    game_screen.draw(Cat_paw);
    game_screen.draw(game_over_text);
    game_screen.display();

   // here im setting a delay  so the user can read professors statement
   // after 5 seconds the next line  will close my game screen automatically
            while (clock.getElapsedTime().asSeconds() < 5) {

    }
    game_screen.close();
}
    }

    return 0;
}
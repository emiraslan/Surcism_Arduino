

// Motor Control
const short M1F = 6;
const short M2F = 9;
const short M1R = 10;
const short M2R = 11;

int M1E = 8; 
int M2E = 8; 

short M1_move = 100;
short M2_move = 100;

short M1_move_s = 65;
short M2_move_s = 65;

short M1_stop = 0;
short M2_stop = 0;

// Infrared - Line Follower
const short leftDisplay = 2;
const short middleDisplay = 5;
const short rightDisplay = 7;

const short initial_delay = 0; 
const short action_delay = 3000; 
const short input_delay = 1;
const short motor_delay = 1; 

const short left = A0;
const short middle = A1;
const short right = A2;

float barrier = 558;

float left_barrier = 580;
float middle_barrier = 480;
float right_barrier = 540;


const char left_dir = 'l';
const char right_dir = 'r';
const char forward_dir = 'f';
const char backward_dir = 'b';

char cur_pos = forward_dir;
char prev_pos = forward_dir;

/*
 directions:
       left = 'l'
       right = 'r'
       forward = 'f'
       background = 'b' 
*/

	// Ultrasonic

#define trigPin 3
#define echoPin 4
#define avioding_dist 25 //cm
#define back_delay 1000 
#define turn_delay 600

int duration;
short distance;


	//Globals
const bool debug_mode = false;

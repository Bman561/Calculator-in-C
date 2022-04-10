#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "leak_detector_c.h"


//Standard function
void remove_crlf(char *s)
{
  char *t = s + strlen(s);
  t--;
  while ((t >= s) && (*t == '\n' || *t == '\r'))
  {
    *t = '\0'; // Clobber the character t is pointing at.
    t--;       // Decrement t.
  }
}


//prints the previous number
double back(FILE *ofp, double *memory, double *store, int count)
{
  char temp[2];
  strcpy(temp, "b");
  while (strcmp(temp, "b") == 0)
  {
    if (count == 0)
    {
      printf("Nothing to go back to. Please press enter to continue. %lf\n", memory[count]);
      fgets(temp, 3, stdin);
      remove_crlf(temp);
    }
    else
    {
      printf("Enter b to go back or continue with enter. %lf\n", memory[count]);
      fprintf(ofp, "b\n");
      fgets(temp, 3, stdin);
      remove_crlf(temp);
      count--;
    }
  }
  return memory[count + 1];
}

void clear_all(FILE *ofp, double *store)
{
  for (int i = 0; i < 10; i++)
  {
    store[i] = 0;
  }
  return;
}

//Function that does the math for Sine
double sine_value(double results, FILE *ofp)
{
  printf("Sine %4.10lf is %4.10lf\n", results, sin(results));
  fprintf(ofp, "Sine %4.10lf is %4.10lf\n", results, sin(results));
  return sin(results);
}

//Function that does the math for Cosine
double cosine_value(double results, FILE *ofp)
{
  printf("Cosine %4.10lf = %4.10lf\n", results, cos(results));
  fprintf(ofp, "Cosine %4.10lf = %4.10lf\n", results, cos(results));
  return cos(results);
}

//Function that does the math Tangent
double tangent_value(double results, FILE *ofp)
{
  printf("Tangent %4.10lf = %4.10lf\n", results, tan(results));
  fprintf(ofp, "Tangent %4.10lf = %4.10lf\n", results, tan(results));
  return tan(results);
}

//Function that does the square root
double square_root(double results, FILE *ofp)
{
  if (results < 0)
  {
    printf("Error\n");
    fprintf(ofp, "Error\n");
  }
  else
  {
    printf("The square root of %4.10lf is %4.10lf\n", results, sqrt(results));
    fprintf(ofp, "The square root of %4.10lf is %4.10lf\n", results, sqrt(results));
  }
  return sqrt(results);
}

//Function that helps figures out the absolute value
double absolute_value_value(double results, FILE *ofp)
{
  printf("The absolute value of %4.10lf is %4.10lf\n", results, fabs(results));
  fprintf(ofp, "The absolute value of %4.10lf is %4.10lf\n", results, fabs(results));
  return fabs(results);
}

//Function that does the inverse 
double inverse_Values(double results, FILE *ofp)
{
  if (results == 0)
  {
    printf("Error.\n");
    fprintf(ofp, "Error.\n");
  }
  else
  {
    printf("The inverse of %4.10lf is %4.10lf\n", results, (1 / results));
    fprintf(ofp, "The inverse of %4.10lf is %4.10lf\n", results, (1 / results));
  }
  return (1 / results);
}

//Function that does the the log base 10 
double log_10(double results, FILE *ofp)
{
  if (results < 0)
  {
    printf("Error.\n");
    fprintf(ofp, "Error.\n");
  }
  else
  {
    printf("The log base 10 of %4.10lf is %4.10lf\n", results, log10(results));
    fprintf(ofp, "The log base 10 of %4.10lf is %4.10lf\n", results, log10(results));
  }
  return log10(results);
}

//Function that prints the log base of 2
double log_2(double results, FILE *ofp)
{
  if (results < 0)
  {
    printf("Error.\n");
    fprintf(ofp, "Error.\n");
  }
  else
  {
    printf("The log of base 2 of %4.10lf is %4.10lf", results, log2(results));
    fprintf(ofp, "The log of base 2 of %4.10lf is %4.10lf", results, log2(results));
  }
  return log2(results);
}

//Save value to memory
int save(double *memory, int count, double value)
{
  count++;
  memory = realloc(memory, sizeof(double) * (count + 1));
  memory[count] = value;
  return count;
}

//First step
double first_input(FILE *ofp, double *memory, double *store, int count)
{
  while (1)
  {
    double value;
    char value_char[128];
    printf("\nInput a value: \n");
    fgets(value_char, 127, stdin);
    remove_crlf(value_char);

    fprintf(ofp, "%s\n", value_char);

    if (strcmp(value_char, "c") == 0 || strcmp(value_char, "clear") == 0)
    {
      printf("0\n");
      fprintf(ofp, "0\n");
      first_input(ofp, memory, store, count);
      break;
    }
    //Exit the program and close file
    else if (strcmp(value_char, "q") == 0 || strcmp(value_char, "quit") == 0)
    {
      free(memory);
      fclose(ofp);
      exit(0);
    }
    //Clear all stored variables
    else if (strcmp(value_char, "ca") == 0 || strcmp(value_char, "clear all") == 0)
    {
      clear_all(ofp, store);
      printf("All memory has been cleared.\n");
      fprintf(ofp, "All memory has been cleared.\n");
      first_input(ofp, memory, store, count);
    }
    //Call back function to go back through the inputs and outputs
    else if (strcmp(value_char, "b") == 0 || strcmp(value_char, "back") == 0)
    {
      value = back(ofp, memory, store, count - 1);
      return value;
      break;
    }
    //Store last double in inputted location
    else if (strcmp(value_char, "sto") == 0 || strcmp(value_char, "store") == 0)
    {
      char temp[256];
      int input;
      printf("Input a number 0-9.\n");
      fprintf(ofp, "Input a number 0-9.\n");
      fgets(temp, 255, stdin);
      input = atoi(temp);

      if (input >= 0 && input <= 9)
      {
        printf("%lf has been stored in location %d.\n", memory[count], input);
        fprintf(ofp, "%lf has been stored in location %d.\n", memory[count], input);
        store[input] = memory[count];
        count = save(memory, count, store[input]);
      }
      else
      {
        printf("Error.\n");
        fprintf(ofp, "Error.\n");
      }
    }
    //Recall double from memory location
    else if (strcmp(value_char, "rcl") == 0 || strcmp(value_char, "recall") == 0)
    {
      char temp[256];
      int input;
      printf("Please Input a number 0 through 9.\n");
      fprintf(ofp, "Please Input a number 0 through 9.\n");
      fgets(temp, 255, stdin);
      input = atoi(temp);

      if (input >= 0 && input <= 9)
      {
        printf("%lf has been recalled from location %d.\n", store[input], input);
        fprintf(ofp, "%lf has been recalled from location %d.\n", store[input], input);
        count = save(memory, count, store[input]);
        return store[input];
        break;
      }
      else
      {
        printf("Error!!!\n");
        fprintf(ofp, "Error!!!\n");
      }
    }
    //Take input double
    else
    {
      value = atof(value_char);
      memory[count] = value;
      return value;
      break;
    }
  }
  return 0;
}

//Second step
void second_input(FILE *ofp, double *store, int count)
{
  char operations[256];
  double first;
  double second;
  double results;
  double *memory = malloc(sizeof(double));

  //Start by getting first number
  first = (first_input(ofp, memory, store, count));

  //Loops the program continuously untill user says stop.
  while (1)
  {
    //This removed random 0 input's or computations I was getting
    if (memory[count] != 0)
    {
      first = memory[count];
    }

    
    //Allocate some memory for your input
    memory = realloc(memory, sizeof(double) * (count + 1));


    //Prompt the user for an operaton
    printf("\nWhat operation do you want to use?\n");
    fgets(operations, 255, stdin);
    remove_crlf(operations);

    //Print values to the tape.txt
    fprintf(ofp, "%lf\n", first);
    fprintf(ofp, "%s\n", operations);


    //Addition 
    if (strcmp(operations, "+") == 0 || strcmp(operations, "addition") == 0)
    {
      count++;
      memory = realloc(memory, sizeof(double) * (count + 1));
      second = (first_input(ofp, memory, store, count));
      count = save(memory, count, (first + second));
      fprintf(ofp, "%lf\n", second);
      printf("The results of %4.10lf + %4.10lf = %4.10lf\n", first, second, first + second);
      fprintf(ofp, "The results of %4.10lf + %4.10lf = %4.10lf\n", first, second, first + second);
    }

    //Subtraction
    else if (strcmp(operations, "-") == 0 || strcmp(operations, "subtaction") == 0)
    {
      count++;
      memory = realloc(memory, sizeof(double) * (count + 1));
      second = (first_input(ofp, memory, store, count));
      count = save(memory, count, (first - second));
      fprintf(ofp, "%lf\n", second);
      printf("The results of %4.10lf - %4.10lf = %4.10lf\n", first, second, first - second);
      fprintf(ofp, "The results of %4.10lf - %4.10lf = %4.10lf\n", first, second, first - second);
    }

    //Multiplication 
    else if (strcmp(operations, "x") == 0 || strcmp(operations, "multiplication") == 0 || strcmp(operations, "*") == 0)
    {
      count++;
      memory = realloc(memory, sizeof(double) * (count + 1));
      second = (first_input(ofp, memory, store, count));
      count = save(memory, count, (first * second));
      fprintf(ofp, "%lf\n", second);
      printf("The results of %lf x %4.10lf = %4.10lf\n", first, second, first * second);
      fprintf(ofp, "The results of %4.10lf x %4.10lf = %4.10lf\n", first, second, first * second);
    }
    //Division 
    else if (strcmp(operations, "/") == 0 || strcmp(operations, "division") == 0)
    {
      count++;
      memory = realloc(memory, sizeof(double) * (count + 1));
      second = (first_input(ofp, memory, store, count));
      if (second == 0)
      {
        printf("Error.\n");
        fprintf(ofp, "Error.\n");
      }
      else
      {
        count = save(memory, count, (first / second));
        fprintf(ofp, "%lf\n", second);
        printf("The results of %4.10lf / %4.10lf = %4.10lf\n", first, second, first / second);
        fprintf(ofp, "The results of %4.10lf / %4.10lf = %4.10lf\n", first, second, first / second);
      }
    }
    //Exponentiation 
    else if (strcmp(operations, "^") == 0 || strcmp(operations, "exponentiation") == 0)
    {
      second = (first_input(ofp, memory, store, count));
      count++;
      fprintf(ofp, "%lf\n", second);
      printf("The results of %4.10lf ^ %4.10lf = %4.10lf\n", first, second, pow(first, second));
      fprintf(ofp, "The results of %4.10lf ^ %4.10lf = %4.10lf\n", first, second, pow(first, second));
    }
    //Sine 
    else if (strcmp(operations, "sin") == 0 || strcmp(operations, "sine") == 0)
    {
      double temp = sine_value(first, ofp);
      count++;
      memory = realloc(memory, sizeof(double) * count + 1);
      count = save(memory, count, temp);
      first = temp;
    }
    //Cosine 
    else if (strcmp(operations, "cos") == 0 || strcmp(operations, "cosine") == 0)
    {
      double temp = cosine_value(first, ofp);
      count++;
      memory = realloc(memory, sizeof(double) * count + 1);
      count = save(memory, count, temp);
      first = temp;
    }
    //Tangent 
    else if (strcmp(operations, "tan") == 0 || strcmp(operations, "tangent") == 0)
    {
      double temp = tangent_value(first, ofp);
      count++;
      memory = realloc(memory, sizeof(double) * count + 1);
      count = save(memory, count, temp);
      first = temp;
    }
   
    //Square roote 
    else if (strcmp(operations, "root") == 0 || strcmp(operations, "square root") == 0)
    {
      double temp = square_root(first, ofp);
      count++;
      memory = realloc(memory, sizeof(double) * count + 1);
      count = save(memory, count, temp);
      first = temp;
    }
    //Absolute value 
    else if (strcmp(operations, "abs") == 0 || strcmp(operations, "remove sign") == 0)
    {
      double temp = absolute_value_value(first, ofp);
      count++;
      memory = realloc(memory, sizeof(double) * count + 1);
      count = save(memory, count, temp);
      first = temp;
    }

    //Inverse 
    else if (strcmp(operations, "inv") == 0 || strcmp(operations, "1/x") == 0)
    {
      double temp = inverse_Values(first, ofp);
      count++;
      memory = realloc(memory, sizeof(double) * count + 1);
      count = save(memory, count, temp);
      first = temp;
    }
    //Log base 10 
    else if (strcmp(operations, "log") == 0 || strcmp(operations, "log10x") == 0)
    {
      double temp = log_10(first, ofp);
      count++;
      memory = realloc(memory, sizeof(double) * count + 1);
      count = save(memory, count, temp);
      first = temp;
    }
    //Log base 2 
    else if (strcmp(operations, "log2") == 0 || strcmp(operations, "log2x") == 0)
    {
      double temp = log_2(first, ofp);
      count++;
      memory = realloc(memory, sizeof(double) * count + 1);
      count = save(memory, count, temp);
      first = temp;
    }
    //Print out a 0 and ask for a new one.
    else if (strcmp(operations, "c") == 0 || strcmp(operations, "clear") == 0)
    {
      first = 0;
      printf("0\n");
      fprintf(ofp, "0\n");
      first_input(ofp, memory, store, count);
    }
    //Clear all the memory stored
    else if (strcmp(operations, "ca") == 0 || strcmp(operations, "clear all") == 0)
    {
      clear_all(ofp, store);
      printf("All memory has been cleared.\n");
      fprintf(ofp, "All memory has been cleared.\n");
      first_input(ofp, memory, store, count);
    }
    //Back command to recall the value or operation sign.
    else if (strcmp(operations, "b") == 0 || strcmp(operations, "back") == 0)
    {
      first = back(ofp, memory, store, count);
    }
    //store the last value that the user inputs
    else if (strcmp(operations, "sto") == 0 || strcmp(operations, "store") == 0)
    {
      char temp[256];
      int input;
      printf("Input a number from 0-9.\n");
      fprintf(ofp, "Input a number from 0-9.\n");
      fgets(temp, 255, stdin);
      input = atoi(temp);

      //Stores the input into designated memory file.

      if (input >= 0 && input <= 9)
      {
        printf("%lf is being stored in %d.\n", memory[count], input);
        fprintf(ofp, "%lf is being stored in %d.\n", memory[count], input);
        store[input] = memory[count];
        count = save(memory, count, store[input]);
      }
      //If not print Error
      else
      {
        printf("Error.\n");
        fprintf(ofp, "Error.\n");
      }
    }

    //Recall the users input memory from (0-9)
    else if (strcmp(operations, "rcl") == 0 || strcmp(operations, "recall") == 0)
    {
      char temp[256];
      int input;
      printf("Input a number 0-9.\n");
      fprintf(ofp, "Input a number 0-9.\n");
      fgets(temp, 255, stdin);
      input = atoi(temp);


      if (input >= 0 && input <= 9)
      {
        printf("%lf has been recalled from location %d.\n", store[input], input);
        fprintf(ofp, "%lf has been recalled from location %d.\n", store[input], input);
        first = store[input];
        count = save(memory, count, store[input]);
      }
      else
      {
        printf("Error.\n");
        fprintf(ofp, "Error.\n");
      }
    }
    //Exits the while loop thus ending the program
    else if (strcmp(operations, "q") == 0 || strcmp(operations, "quit") == 0)
    {
      break;
    }
    //Prompt the user that they made an invalid operation
    else
    {
      printf("Invalid Operator please try again! \n");
      fprintf(ofp, "Invalid Operator please try again! \n");
    }
  }

  //Free up the memory to avoid memory leaks
  free(memory);
  fclose(ofp);
}
//Main!
int main()
{
  //atexit(report_mem_leak);
  double store[10];
  int count = 0;
  FILE *ofp = fopen("Tape.txt", "w");
  second_input(ofp, store, count);
  
  fclose(ofp);
  return 0;
}
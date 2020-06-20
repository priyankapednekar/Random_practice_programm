//
// programming exercise
//  Author:  Priyanka Pednekar
//  Date :3/19/17
/*
 You are given a deck containing N cards. While holding the deck:
 1. Take the top card off the deck and set it on the table
 2. Take the next card off the top and put it on the bottom of the deck in your hand.
 3. Continue steps 1 and 2 until all cards are on the table. This is a round.
 4. Pick up the deck from the table and repeat steps 1-3 until the deck is in the original order.
 */
//This program uses struct as data structure element.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Card
{
     char *suit;
     char *face;
     struct Card *next;
    
};

typedef struct Card card;

struct Deck {
    int card_num;
    card **cards;
    card *top;
    card *bottom;
    
};


typedef struct Deck deck;


//function to create card
card *new_card(char *suit, char *face)
{
    card *newcard = malloc(sizeof(card));
    newcard->suit = suit;
    newcard->face = face;
    newcard->next = NULL;
    
    return newcard;
}

//function to create new deck of specified size
deck *new_deck(int size)
{
    
    char *suit_cards[4]={"C","D","H","S"};
    char *face_cards[13]={"1","2","3","4","5","6","7","8","9","10","11","12","13"};
    
    
    deck *newdeck = malloc(sizeof(deck));
    
    newdeck->card_num = size;
    newdeck->cards = malloc(size * sizeof(card *));
    newdeck->top=NULL;
    newdeck->bottom=NULL;
    
    
    int k= 0;
    int i=0;
    int j=0;
    
        for (i  = 0; i < 4; i++)
        {
            for (j = 0; j < 13; j++)
            {
                newdeck->cards[k] = new_card (suit_cards[i], face_cards[j]);
                
                newdeck->cards[k]->next=newdeck->top;
                newdeck->top=newdeck->cards[k];
                
                
                if (k==0)
                {
                    
                    newdeck->bottom=newdeck->cards[k];
                    newdeck->bottom->next=NULL;
                    
                }
                
                k++;
                if (k>=size)
                  return newdeck;
            }
        }
    
    
    return newdeck;
}



//this is function to perform one round
deck * one_round(deck * const vdeck,int size)
{
    
    deck *init = vdeck;//deck in hand
    
    deck *floor = malloc(sizeof(deck));//deck on table
    floor->card_num = size;
    floor->cards = malloc(size * sizeof(card *));
    floor->top=NULL;
    floor->bottom=NULL;
    
    
    card *top_card=NULL; //card which picked from top of deck
    
    card *temp=NULL;
    
    card *top_card_next=NULL;

    int f=0;


    while(1)
    {
        
        top_card=init->top;
        init->top=init->top->next;
        
        
        if (top_card==NULL)
            break;
        
        //adding card to table top
        if (floor->top==NULL)
        {
            floor->cards[f]= top_card;
            floor->top=top_card;
            floor->bottom=top_card;
            floor->cards[f]->next=NULL;
            f++;
        }
        else
        {
            floor->cards[f]= top_card;
            floor->cards[f]->next=floor->top;
            floor->top=floor->cards[f];
            f++;
        }
        
        if (init->top==NULL)
            break;
        
        
        //getting from top
        top_card=init->top;
        top_card_next=init->top->next;
        
        
        if (top_card==NULL)
            break;
        
        //adding card to bottom of hand
        if (top_card_next==NULL)
        {
            init->top=top_card;
            init->top->next=NULL;
            
        }
        else
        {
            temp=new_card(top_card->suit, top_card->face);
            
            
            init->top=top_card_next;
            
            temp->next=NULL;
            init->bottom->next=temp;
            init->bottom=temp;
            
        }
        
        
    }
    


return floor;

}

//this function comapre deck to find condition come out of program.
int compare_deck(deck * const arg1, deck * const arg2,int c)
{
    int flag=0;
    int i=0;
    
    for (i =c-1; i >=0; i--)
    {

        if (strcmp(arg1->cards[i]->face,arg2->cards[i]->face)==0 && strcmp(arg1->cards[i]->suit,arg2->cards[i]->suit)==0)
            {
                flag=1;
            
            }
        else
            {
                flag=0;
                return flag;
            }
    
    }
    
    return flag;
}


//this function perform all round until the deck gets set
int full_round(deck * const vdeck,int size)
{
    int count=1;
    
    deck *val=vdeck;
    
    int flag=0;
    int i=0;

    while (1)
    {
    
    val = one_round(val,size);
    
    printf("==============\n");
    for (i =size-1; i >=0; i--)
       printf("Round %d: %s %s\n",count, val->cards[i]->suit, val->cards[i]->face);
        
        
    flag=compare_deck(val,vdeck, size);
        
    if(flag==1)
        {
            break;
        }
        
    count+=1;
        
    }
    
    
    return count;
}


//main function which take number of count as command line argument.
int main(int argc, char **argv)
{
    
    int deck_size=atoi(argv[1]);
    int i=0;
    
    if (deck_size<=0)
    {
     printf("Number of cards in deck can not be Zero or negative!!\n");
        exit(-1);
    }
    
    deck *shdeck = new_deck(deck_size);
    
    int count=0;
    
    //printing cards in hand
    for (i =deck_size-1; i >=0; i--)
      printf("Initial deck %s %s\n", shdeck->cards[i]->suit, shdeck->cards[i]->face);
    
    
    //calling function for making round 1-4
    count = full_round(shdeck,deck_size);
    
    printf("==============\n");
    printf("==============\n");
    printf("Total Round performed %d\n", count);

  
    //deallocating memory
    for (i = 0; i <deck_size; i++)
        free(shdeck->cards[i]);
    free(shdeck->cards);
    free(shdeck->top);
    free(shdeck->bottom);
    free(shdeck);
    
    
    return 0;
    
}

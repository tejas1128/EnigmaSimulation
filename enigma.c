#include<stdio.h>
#include<stdlib.h>

char pairs[26][3];

char text[1000];

int r1,r2,r3;

void printMessage(){
    int i;
    for(i=0;text[i]!='\0';i++){
        printf("%c",text[i]);
    }
}

char compare(char x){
    int j=0;
    	
    	if(x == ' '){
    		return ' ';
		}
		
        for(j=0;j<26;j++){
            if(x == pairs[j][0]){
                x = pairs[j][1];
            }
            else if(x == pairs[j][1]){
                x = pairs[j][0];
            }
        }
        return x;
}

void interChange(){
    int i=0,j=0;
    for(i=13;i<26;i++){
        pairs[i][0] = pairs[j][0] - 32;
        pairs[i][1] = pairs[j][1] - 32;
        j++;
    }
}

char decode(char x, int n){
    
    if(x == ' '){
        x = ' ';
    }
    else if(x > 96 && x < 123){
        if(x - n < 97){
            n = n + (97 - x);
            n = n%26;
            x = 123-n;
        }
        else{
            x = x - n;
        }
    }
    else if(x > 64 && x < 91){
        if(x - n < 65){
            n = n + (65 - x);
            n=n%26;
            x = 91-n;
        }
        else{
            x = x - n;
        }
    }
    x = compare(x);
    return x;
}

char encode(char x, int n){
    if(x == ' '){
        x = ' ';
    }
    else if(x > 96 && x < 123){           // creates a link between a and z
        if(x + n > 122){
            n = n- (122-x);
            n = n%26;
            x = 96 + n;
        }
        else{
            x = x + n;
        }
    }
    else if(x > 64 && x < 91){           // creates a link between A and Z
        if(x + n > 90){
            n = n - (90 - x);
            n = n%26;
            x = 64 + n;
        }
        else{
            x = x + n;
        }
    }
    x = compare(x);
    return x;
}

char moveRotor1(char x, int r1){
   
    x = encode(x,r1);
    return x;
}

char moveRotor2(char x, int r2){
   
    x = encode(x,r2);
    return x;
}

char moveRotor3(char x, int r3){
    
    x = encode(x,r3);
    return x;
}

char moveRotor1R(char x, int r1){
   
    x = decode(x,r1);
    return x;
}

char moveRotor2R(char x, int r2){
   
    x = decode(x,r2);
    return x;
}

char moveRotor3R(char x, int r3){
    
    x = decode(x,r3);
    return x;
}

void crudeEnigmaEncode(){
    int i,j=0,ch=0;
    char x;
    printf("Enter the text : ");

    scanf("\n");
    scanf("%[^\n]%*c",text);

    for(i=0;text[i]!='\0';i++){
        x = text[i];
        for(j=0;j<26;j++){
            if(x == pairs[j][0]){
                x = pairs[j][1];
            }
            else if(x == pairs[j][1]){
                x = pairs[j][0];
            }
        }
//		printf("x before rotor %c\n",x);
        x = moveRotor1(x,r1);
//        printf("x after one %c\n",x);
        x = moveRotor2(x,r2);
//        printf("x after two %c\n",x);
        x = moveRotor3(x,r3);
//        printf("x after three %c\n",x);
        
        text[i] = x;

        continue;
    }
    printf("\nThe encrypted message is : ");
    printMessage();
    printf("\nUse %d %d %d as keys to decrypt the messages\n",r1,r2,r3);

}

void crudeEnigmaDecode(){
    int i=0,j=0;
    char x;
    
	printf("Enter the text : ");

	scanf("\n");
    scanf("%[^\n]%*c",text);
    
    for(i=0;text[i]!='\0';i++){
        x = text[i];
        for(j=0;j<26;j++){
            if(x == pairs[j][0]){
                x = pairs[j][1];
            }
            else if(x == pairs[j][1]){
                x = pairs[j][0];
            }
        }

        x = moveRotor3R(x,r3);
        x = moveRotor2R(x,r2);
        x = moveRotor1R(x,r1);
        
        text[i] = x;
        continue;
    }
    
    printf("The decrypted message is : ");
    printMessage();
}

void makeDefault(){

}

int main(){

    int i=0,j=0,ch, count=0, def=0;

    printf("\n\nThe message should all be in upperCase or lowerCase or space.. Dont use any special character or full stop.. For better understanding use CamelCase Letters\n");

    while(1){
    	if(count == 0){
		
		    printf("Enter the pairs\n");
            
            for(i=0;i<13;i++){
                scanf("%s",pairs[i]);
            }
		    count++;
		    interChange();
		}
		
        printf("\n\n\n1.Encode\n2.Decode\n3.Exit\nEnter your choice : ");  scanf("%d",&ch);
        if(ch == 3) break;
        printf("There will be only 3 rotors to encode\n");
        printf("Enter rotor value 1 : "); scanf("%d",&r1); r1 %= 26;
        printf("Enter rotor value 2 : "); scanf("%d",&r2); r2 %= 26;
        printf("Enter rotor value 3 : "); scanf("%d",&r3); r3 %= 26;
        switch(ch){
            case 1:{
                crudeEnigmaEncode();
                break;
            }
            case 2:{
                printf("Decrpting the message : \n");
                crudeEnigmaDecode();
                break;
            }
            case 3:
                exit(0);
        }
    }

    return 0;
}

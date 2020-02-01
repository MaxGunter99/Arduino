# include <LiquidCrystal.h>

LiquidCrystal lcd( 7, 8, 9 , 10, 11, 12 );

const int VRx = 0; // Connect to Analog Pin 0
const int VRy = 1; // Connect to Analog Pin 1
const int SW = 4; // Connect to Digital Pin 4

int XIndex = 0;
int YIndex = 0;
bool start = false;

int enemy = 0;
int EnemyIndexX = 15;
int EnemyIndexY = rand() % 2;
//int EnemyIndexY = 0;

void setup() {

  lcd.begin( 16, 12 );
  lcd.setCursor( 0, 0 );
  pinMode(SW, INPUT);
  digitalWrite(SW, HIGH);
  Serial.begin(9600);

  while ( start == false ) {

    if ( digitalRead(SW) == 0 ) {
        bool start = true;
        return start;
    }

    lcd.begin( 16, 12 );
    lcd.setCursor( 1, 0 );
    lcd.print( "Space Invaders" );
    delay( 700 );

    lcd.setCursor( 1, 0 );
    lcd.print( "Space Invaders" );
    lcd.setCursor( 1, 1 );
    lcd.print( "Press to start" );
    delay( 1000 );

    if ( digitalRead(SW) == 0 ) {
        bool start = true;
        return start;
    }

  }


}

void loop() {
  
// WARNING THIS MAKES THE GAME SO HARD
  int EnemyIndexY = rand() % 2;

  // begin at 0 , 1

  // No movement at x: 489, y: 508, Button: 1 ( 0 of pressed )

  // Up: x > 600
  // Down: x < 350

  // Left : y < 400
  // Right: y > 800

  const int x = analogRead(VRx);
  const int y = analogRead(VRy);
  const int b = digitalRead(SW);

  const int chance = rand() % 4;


  lcd.begin( 16, 12 );
  lcd.setCursor( XIndex, YIndex );
  lcd.print( "~" );

  if ( chance < 1 ) {

    if ( enemy < 1 ) {
      enemy = enemy + 1;
      MoveEnemy( 0 );

    }

  }

  if ( enemy > 0 ) {
    lcd.setCursor( EnemyIndexX, EnemyIndexY );
    EnemyIndexX = EnemyIndexX - 1;
    lcd.print( "*" );
  }

  // MOVEMENT
  if ( x > 600 ) {

    //    lcd.print( "UP" );
    if ( YIndex > 0 ) {
      YIndex = YIndex - 1;
    }

  } else if ( x < 350 ) {

    //    lcd.print( "DOWN" );
    if ( YIndex < 1 ) {
      YIndex = YIndex + 1;
    }

  } else if ( y > 800 ) {

    //    lcd.print( "RIGHT" );
    if ( XIndex < 15 ) {
      XIndex = XIndex + 1;
    }

  } else if ( y < 400 ) {

    //    lcd.print( "LEFT" );
    if ( XIndex > 0 ) {
      XIndex = XIndex - 1;
    }

  } else if ( b < 1 ) {

    int bulletX = XIndex + 1;
    int bulletY = YIndex;

    Shoot();

  }

  if ( EnemyIndexX == 0 ) {
    lcd.begin( 16, 12 );
    lcd.setCursor( 6 , 0 );
    lcd.print( "GAME" );
    lcd.setCursor( 6 , 1 );
    lcd.print( "OVER" );
    delay(1000000000);
  }

  delay(100);

}

void MoveEnemy ( int x ) {

  int i = 15;

  while ( i > 0 && enemy > 0 ) {
    
    // Alien Speed
    delay( 50 );
    
    i = i + 1;
    
    loop();


  }

}

void Shoot () {

  int bulletX = XIndex + 1;
  int bulletY = YIndex;
  int i = bulletX;

  while ( i < 16 ) {

    lcd.begin( 16, 12 );
    lcd.setCursor( XIndex, YIndex );
    lcd.print( "~" );

    lcd.setCursor( EnemyIndexX, EnemyIndexY );
    lcd.print( "*" );

    lcd.setCursor( bulletX, bulletY );
    bulletX = bulletX + 1;
    lcd.print( "-" );

    if ( bulletX == EnemyIndexX) {

      if ( bulletY == EnemyIndexY  ) {
        enemy = 0;
        lcd.begin( 16, 12 );

        lcd.setCursor( bulletX, bulletY );
        lcd.print( "x" );

        lcd.setCursor( XIndex, YIndex );
        lcd.print( "~" );

        delay(100);

        lcd.setCursor( bulletX, bulletY );
        lcd.print( "X" );
        
        delay( 100 );
        
        i = 16;
        
        EnemyIndexX = 15;
        EnemyIndexY = 0;
        enemy = 0;
        i = 16;
        
      }

    }
    
    i = i + 1;
    
    delay( 50 );



  }

}

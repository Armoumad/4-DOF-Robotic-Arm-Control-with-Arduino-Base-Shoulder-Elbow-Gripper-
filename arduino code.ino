#include <Servo.h>

// Créer les objets servos
Servo base;
Servo shoulder; 
Servo elbow;
Servo gripper;

// Pins des servos
const int BASE_PIN = 6;
const int SHOULDER_PIN = 3;
const int ELBOW_PIN = 5;
const int GRIPPER_PIN = 9;

void setup() {
  Serial.begin(115200);
  
  // Attacher les servos aux pins
  base.attach(BASE_PIN);
  shoulder.attach(SHOULDER_PIN);
  elbow.attach(ELBOW_PIN);
  gripper.attach(GRIPPER_PIN);
  
  // Position initiale (position sûre)
  base.write(90);
  shoulder.write(90);
  elbow.write(90);
  gripper.write(0);
  
  // Afficher les instructions
  Serial.println("===================================");
  Serial.println("   CONTROLE DES SERVOS MOTEURS");
  Serial.println("===================================");
  Serial.println();
  Serial.println("COMMANDES DISPONIBLES:");
  Serial.println("  B angle  -> Contrôler la BASE");
  Serial.println("  S angle  -> Contrôler l'EPAULE");  
  Serial.println("  E angle  -> Contrôler le COUDE");
  Serial.println("  G angle  -> Contrôler la PINCE");
  Serial.println();
  Serial.println("EXEMPLES:");
  Serial.println("  B 90     (base à 90°)");
  Serial.println("  S 45     (épaule à 45°)");
  Serial.println("  E 120    (coude à 120°)");
  Serial.println("  G 30     (pince à 30°)"a);
  Serial.println("===================================");
  Serial.println();
}

void loop() {
  // Vérifier si des données sont disponibles
  if (Serial.available() > 0) {
    // Lire la commande
    String commande = Serial.readStringUntil('\n');
    commande.trim(); // Enlever les espaces
    
    // Vérifier la longueur minimale
    if (commande.length() >= 3) {
      // Extraire le servo et l'angle
      char servo = commande.charAt(0);
      String angleStr = commande.substring(2);
      int angle = angleStr.toInt();
      
      // Limiter l'angle enele, 0, 180);
      
      // Convertir en majuscule
      servo = toupper(servo);
      
      // Contrôler le servo correspondant
      switch(servo) {
        case 'B':
          base.write(angle);
          Serial.print("Base -> ");
          Serial.print(angle);
          Serial.println("°");
          break;
          
        case 'S':
          shoulder.write(angle);
          Serial.print("Épaule -> ");
          Serial.print(angle);
          Serial.println("°");
          break;
          
        case 'E':
          elbow.write(angle);
          Serial.print("Coude -> ");
          Serial.print(angle);
          Serial.println("°");
          break;
          
        case 'G':
          gripper.write(angle);
          Serial.print("Pince -> ");
          Serial.print(angle);
          Serial.println("°");
          break;
          
        default:
          Serial.println("Erreur: Servo inconnu!");
          Serial.println("Utilisez: B, S, E ou G");
          break;
      }
    }
    else {
      Serial.println("Format incorrect!");
      Serial.println("Format: LETTRE ANGLE");
      Serial.println("Exemple: B 90");
    }
  }
}
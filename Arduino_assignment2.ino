// Task 5: Putting It All Together — Beeping Countdown

// Define hardware pins
int buzzerPin = 8;
int segmentPins[] = {2, 3, 4, 5, 6, 7, 9}; // a, b, c, d, e, f, g (pin 8 is buzzer)
int numSegments = 7;

// The 2D array lookup table for each digit pattern from Task 4
// 1 = segment ON, 0 = segment OFF
byte digits[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

// Function to display a specific digit on the 7-segment display
void showDigit(int n) {
  // Safety check: do nothing if input is out of bounds
  if (n < 0 || n > 9) return;

  // Loop through each of the 7 segments and apply the matching pattern
  for (int i = 0; i < numSegments; i++) {
    digitalWrite(segmentPins[i], digits[n][i]);
  }
}

void setup() {
  // 1. Initialize Serial communication
  Serial.begin(9600);
  Serial.println("=== Beeping Countdown Starting ===");

  // 2. Set the buzzer pin as an OUTPUT
  pinMode(buzzerPin, OUTPUT);

  // 3. Set every segment pin as an OUTPUT and ensure they start OFF
  for (int i = 0; i < numSegments; i++) {
    pinMode(segmentPins[i], OUTPUT);
    digitalWrite(segmentPins[i], LOW);
  }

  // 4. Use a while loop to count down from 9 to 1
  int count = 9;
  while (count >= 1) {
    // Print the current count to the Serial Monitor
    Serial.print("Counting: ");
    Serial.println(count);

    // Show the digit on the 7-segment display
    showDigit(count);

    // Play a short beep (1000 Hz for 200 ms)
    tone(buzzerPin, 1000, 200);

    // Wait 1 second before moving to the next step
    delay(1000);

    // Decrement the counter
    count--;
  }

  // 5. When the countdown reaches 0: show 0 on the display
  Serial.print("Counting: ");
  Serial.println(0);
  showDigit(0);

  // Play a longer "completion" tone (1500 Hz for 1000 ms)
  tone(buzzerPin, 1500, 1000);
  delay(1000); // Allow the tone and visual to be observed fully

  // Print completion message to Serial Monitor
  Serial.println("=== Countdown Complete ===");
}

void loop() {
  // loop() is intentionally left empty as everything runs once in setup()
}
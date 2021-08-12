# Proiect_criptare-decriptare-imagine-si-template-matching
Encryption:

![what-is-encryption](https://user-images.githubusercontent.com/48885998/76467525-7a1a4980-63f2-11ea-9153-a1147d9b1282.png)

1.Pixel permutation                                                        
Before:

![peppers](https://user-images.githubusercontent.com/48885998/76458797-c3af6800-63e3-11ea-815f-0cdb4acdf0f7.png)

After:

![49013306_603160036780183_6947998281553149952_n](https://user-images.githubusercontent.com/48885998/76466424-57873100-63f0-11ea-8c8d-5938ba008bd5.jpg)

First step is reading the image (file) as an 1-dimensional array. Next is pixel permutation in a pseudo-random pattern (with an Xorshift32 function with a secret seed, that returns each time a different number). 

2. Encryption
After:

![criptat](https://user-images.githubusercontent.com/48885998/76466871-1b080500-63f1-11ea-9fd4-dd403da1ae10.png)

We use values obtained from Xorshift32 again for the encryption part, each pixel receives a new value of the pseudo-random number ^(Xor) its old value ^(Xor) secret key.

3.Decryption:
We repeat the same steps in reverse. As for the Xor operation, a number Xor itself is 0, so we can obtain the old values of the pixels, and then re-order them back.


Template matching:

![template](https://user-images.githubusercontent.com/48885998/76468032-a1bde180-63f3-11ea-97fe-60b771aea20d.jpg)

First we read the image that contains hand-written digits. The program must recognize them with the digit templates on the right, and mark them with rectangles of a different color for each digit (for example, 5's will be in blue rectangles etc).

![87805819_3381952768488774_5928497419145707520_n](https://user-images.githubusercontent.com/48885998/76468332-62dc5b80-63f4-11ea-8dfc-891b349ced9f.jpg)

For each pixel in the image, the program will have a rectangle to work on - the pixel is the rectangle's first pixel starting from its upper corner on the left. Next, it calculates the correlation (given by a mathematical formula) between this rectangle and each template, and if the correlation is higher than 0.5, it draws a colored rectangle depending on the digit-template. After that, the image will be filled with intersecting rectangles, which are eliminated, leaving only the ones with the highest correlation. The correlation is calculated based on the value of the pixels and their position, in other words it is a factor of resemblance between the template and the rectangle.

![template2](https://user-images.githubusercontent.com/48885998/76468920-cf0b8f00-63f5-11ea-9a70-e2cea2484fb8.jpg)

(Acesta este un proiect din 2 parti: prima e criptarea si decriptarea unei imagini, a doua consta din template matching. 
Primul pas spre criptare este citirea imaginii intr-un vector 1-dimensional (tinand cont si de octetii de padding), apoi permutarea pixelilor cu ajutorul unei functii de generare de numere pseudo-random utilizand o valoare de seed: Xorshift32.  Dupa care se utilizeaza valorile obtinute din Xorshift32 din nou pentru criptare, Xor-ind cu vectorul permutat si cheia secreta. Pentru decriptare urmarim aceeasi pasi in ordine inversa.
Pentru template matching, din nou, citim imaginea, care consta din cifre scrise de mana. Avem si sabloane cu cifre scrise de tipar, pentru a face comparatia. Acest algoritm gaseste cifrele scrise de mana si aplica un chenar de o anumita culoare pentru cifra corespunzatoare (exemplu: cifrele de 5 au chenar albastru). Pentru fiecare pixel din imaginea stabilim un chenar (pixelul este cel din coltul de sus, dreapta a chenarului), pentru care chemam functia ce calculeaza corelatia dintre chenar si fiecare sablon (0-9) dupa o functie matematica, corelatia este stabilita conform valorii pixelilor (de la 0 la 255, fiindca imaginile sunt alb-negru) si pozitiile acestora. Daca corelatia depaseste 0.5, aplicam chenarul in functie de sablonul pentru care am obtinut corelatia. In final vom avea multe chenare suprapuse, unele dintre care sunt in plus. Eliminam chenarele cu corelatia mai mica in caz ca avem 2 care se suprapun.)


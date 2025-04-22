I wanted a way to scan my Magic the Gathering cards, store them in a database somewhere, and be able to search for them easily. There are apps that do this, Manabox being one of the more popular examples, but they all have fees or charge for subscriptions, or are generally kind of goofy. So, I decided to just make my own using Tesseract OCR and a pretty simple rig I built out of a deskbox and an old webcam.

---

If you're interested in using this code, it's important to:
1. Have Tesseract OCR and Leptonica downloaded. These can both be found in the tesseract docs, linked [here.](https://tesseract-ocr.github.io/tessdoc/)
2. Have a way to ensure that the cards are always in the same place in the frame, or a way to crop images taken with your chosen camera. I went with the first option and just built a physical rig, because it sounded more fun at the time.
3. Be able to greyscale and set the image dpi to 300 before processing it through tesseract. This just generally helps with reading the text, as tesseract can be kind of finicky with what it can actually parse. I use OpenCV for this.

---

To make sure I only got the information I needed to identify specific cards, in my case the name and set number, I used the Rectangles feature of tesseract to draw boxes around where they would normally be. To find the coordinates, running tesseract on the command line is more useful than running it through our code as we can output the detection data into a tsv. This can be done with the command
```
tesseract -l eng {location-of-image.png} out tsv --psm 4
```
which instructs tesseract to look for english words in Page Segmentation Mode (psm) 4, which assumes a single column of text with sentences of varying lengths, and to output its findings to a tsv. The output will include four columns labelled left, top, width, height, which are used by the SetRectangle function in the actual code we write. Finding the coordinates for the data you want, and tweaking them to ensure the information is being collected properly in your code, should ensure a consistent ability to read any standard-formatted card every time, as long as your cards are in the same place every time. With the example image provided, I had to shift all four of the numbers extremely slightly, left and top should only decrease while height and width should only increase. For your first test, I would recommend choosing a card with the longest possible name to ensure you are able to pick up the whole name box. Set codes are significantly more consistent, being only 4 characters maximum.

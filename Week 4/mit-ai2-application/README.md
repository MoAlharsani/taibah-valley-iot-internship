# Random Person Generator App using MIT App Inventor

## Overview
This project demonstrates how to create a simple mobile app using MIT App Inventor that generates random images of non-existent people. The app fetches images from the website "thispersondoesnotexist.com" and displays a new image each time the "Generate" button is clicked.

## Requirements
- MIT App Inventor (http://ai2.appinventor.mit.edu)
- Internet connection

## Setup

### Creating the App
1. Open MIT App Inventor in your browser and create a new project.
2. Design your app interface with a Button component named "Generate" and an Image component to display the generated images.
3. Add appropriate labels or instructions to guide users.

### Fetching Images
1. Use the Web component to send a request to the URL "https://thispersondoesnotexist.com" when the "Generate" button is clicked.
2. Handle the response using the Web component's `GotText` event. This response will be the image URL.
3. Set the Image component's Picture property to the received URL to display the generated image.

## How It Works
1. The user opens the app on their mobile device.
2. Upon clicking the "Generate" button, the app sends a request to "thispersondoesnotexist.com" to fetch a new random image.
3. The website generates and returns an image URL as a response.
4. The app displays the fetched image in the Image component.

## App Preview
![App Inventor App Preview](/img/app_preview.jpeg)

## Conclusion
With MIT App Inventor, you've created a simple app that uses the website "thispersondoesnotexist.com" to generate random images of nonexistent people. This project demonstrates how to interact with web APIs and display images in a mobile app interface. By following these steps, you've learned how to build a basic app with dynamic content.

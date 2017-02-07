## Food Rating API

Technologies used: Node.js, Express.js, QuickBlox

**Summary:** This API interacts with a database for food ratings.

**Usage:**

**GET: http://{URL}:{port}/food/**
+ This will retrieve all records in the food-rating table
+ The data retrieved will show:
..* _id
..* foodname
..* price
..* rating
..* restaurantname
..* city
..* state

**POST: http://{URL}:{port}/food/**
+ This allows you to add new records to the food-rating table
+ Use Content-Type: application/x-www-form-urlencoded
+ Any attributes omitted will become null values in the database
+ Data types for each attribute:
..* foodname - string
..* price - float
..* rating - integer
..* restaurantname - string
..* city - string
..* state - string

**PUT: http://{URL}:{port}/food{/_id}**
+ This changes values of existing records
+ Use Content-Type: application/x-www-form-urlencoded

**DELETE: http://{URL}:{port}>/food{/_id}**
+ This deletes an existing record using its _id
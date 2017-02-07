## Food Rating API

Technologies used: Node.js, Express.js, QuickBlox

**Summary:** This API interacts with a database for food ratings.

**Usage:**

**GET: http://{URL}:{port}/food/**
+ This will retrieve all records in the food-rating table
+ The data retrieved will show:
1. _id
2. foodname
3. price
4. rating
5. restaurantname
6. city
7. state

**POST: http://{URL}:{port}/food/**
+ This allows you to add new records to the food-rating table
+ Use Content-Type: application/x-www-form-urlencoded
+ Any attributes omitted will become null values in the database
+ Data types for each attribute:
1. foodname - string
2. price - float
3. rating - integer
4. restaurantname - string
5. city - string
6. state - string

**PUT: http://{URL}:{port}/food{/_id}**
+ This changes values of existing records
+ Use Content-Type: application/x-www-form-urlencoded

**DELETE: http://{URL}:{port}>/food{/_id}**
+ This deletes an existing record using its _id
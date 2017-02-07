## Food Rating API

Technologies used: Node.js, Express.js, QuickBlox

Usage:

-GET: http://<URL>:<port>/food/
 This will retrieve all records in the food-rating table
 The data retrieved will show:
o _id
o foodname
o price
o rating
o restaurantname
o city
o state

-POST: http://<URL>:<port>/food/
 This allows you to add new records to the food-rating table
 Use Content-Type: application/x-www-form-urlencoded
 Any attributes omitted will become null values in the database
 Data types for each attribute:
o foodname - string
o price - float
o rating - integer
o restaurantname - string
o city - string
o state - string

-PUT: http://<URL>:<port>/food{/_id}
 This changes values of existing records
 Use Content-Type: application/x-www-form-urlencoded

-DELETE: http://<URL>:<port>/food{/_id}
 This deletes an existing record using its _id
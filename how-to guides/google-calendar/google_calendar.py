import urllib2
import json


emailInput = "leima@oregonstate.edu manhing@gmail.com"

dateInput = "2016-01-28" #will take in from user input 
earliestTime = dateInput + "T00:00:00-08:00"  # -08:00 is PST; -07:00 is PDT (consider this in your API calls)
latestTime = dateInput + "T23:59:00-08:00"

emailList = [] # declare new list
emailList = emailInput.split() #create email list delimited by space character


#for each email address
for index, elem in enumerate(emailList):

	try:
		# API call to Google Calendars API; timeMin is set to 00:00 and timeMax is set to 23:59, 
		# so we're going to get all events of that day
		response = urllib2.urlopen("https://www.googleapis.com/calendar/v3/calendars/"+emailList[index]+
			"/events?timeMin="+earliestTime+"&timeMax="+latestTime+"&key=AIzaSyB7IsERaXNIMiRgMAB_tujhdzNVmxpq0KA").read()
		print response

	except urllib2.HTTPError, e:
		print "\nERROR: We could not retrieve the calendar for", emailList[index]
		print e #print error status
		continue


		print emailList[index] #prints the Google account
		responseJson = json.loads(response) #converts to JSON object
		for idx, item in enumerate(responseJson['items']): #for every event
			eventName = responseJson['items'][idx]['summary']
			startDateTime = responseJson['items'][idx]['start']
			endDateTime = responseJson['items'][idx]['end']

			print eventName
			print startDateTime
			print endDateTime
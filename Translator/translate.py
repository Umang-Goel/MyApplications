#### Author ####
#### Umang Goel ####
#### This program would take string and the target language as the input and print the translated string #####
 
import urllib
import urllib2
import json

def genQuery(s):
	url = "http://query.yahooapis.com/v1/public/yql"
	s1 = urllib.quote_plus(s)
	query = {'q':s1,'target':'hi','format':'json'}
	data = urllib.urlencode(query)
	tmp = urllib2.Request(url,data)
	res = urllib2.urlopen(tmp)
	return res

def getPage(words,dest):
	words = urllib.quote_plus(words)
	url = "http://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20google.translate%20where%20q%3D%22" + words +"%22%20and%20target%3D%22" + dest + "%22%3B&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys&callback="
	headers = { 'User-Agent' : 'Mozilla/5.0' }
	req = urllib2.Request(url, None, headers)
	response = urllib2.urlopen(req)
	return response.read()

def parseJsonResult(resultStr):
	result = json.loads(resultStr)
	#resultArray = result['query']['results']['json']['sentences']
	resultArray = result['query']['results']['json']['sentences']['trans']
	return resultArray

inpStr = raw_input("Enter String to be Translated\n")
target = raw_input("Enter target language\n")

t1= getPage(inpStr,target)
print parseJsonResult(t1)

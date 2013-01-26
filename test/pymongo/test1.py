#!/usr/bin/python

import pymongo
import datetime
from pymongo import MongoClient
connection = MongoClient("localhost", 27017)
db = connection['test_database']
#db = connection.test_database is the same with db = connection['test_database']

collection = db.test_collection
post = {"author": "lei", "text": "My test post"}
posts = db.posts
posts.insert(post)

for pos in posts.find():
	print pos
	posts.remove(pos)

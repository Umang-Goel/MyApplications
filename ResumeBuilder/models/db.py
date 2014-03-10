# -*- coding: utf-8 -*-

#########################################################################
## This scaffolding model makes your app work on Google App Engine too
## File is released under public domain and you can use without limitations
#########################################################################

## if SSL/HTTPS is properly configured and you want all HTTP requests to
## be redirected to HTTPS, uncomment the line below:
# request.requires_https()

if not request.env.web2py_runtime_gae:
    ## if NOT running on Google App Engine use SQLite or other DB
    db = DAL('sqlite://storage.sqlite',pool_size=1,check_reserved=['all'])
else:
    ## connect to Google BigTable (optional 'google:datastore://namespace')
    db = DAL('google:datastore')
    ## store sessions and tickets there
    session.connect(request, response, db=db)
    ## or store session in Memcache, Redis, etc.
    ## from gluon.contrib.memdb import MEMDB
    ## from google.appengine.api.memcache import Client
    ## session.connect(request, response, db = MEMDB(Client()))

## by default give a view/generic.extension to all actions from localhost
## none otherwise. a pattern can be 'controller/function.extension'
response.generic_patterns = ['*'] if request.is_local else []
## (optional) optimize handling of static files
# response.optimize_css = 'concat,minify,inline'
# response.optimize_js = 'concat,minify,inline'

#########################################################################
## Here is sample code if you need for
## - email capabilities
## - authentication (registration, login, logout, ... )
## - authorization (role based authorization)
## - services (xml, csv, json, xmlrpc, jsonrpc, amf, rss)
## - old style crud actions
## (more options discussed in gluon/tools.py)
#########################################################################

from gluon.tools import Auth, Crud, Service, PluginManager, prettydate
auth = Auth(db)
crud, service, plugins = Crud(db), Service(), PluginManager()

## create all tables needed by auth if not custom tables
auth.define_tables(username=False, signature=False)

## configure email
mail = auth.settings.mailer
mail.settings.server = 'students.iiit.ac.in:25' # 'smtp.gmail.com:587'
mail.settings.sender = 'umang.goel@students.iiit.ac.in'
mail.settings.login =  'umang.goel:umang27/05/1994'

## configure auth policy
auth.settings.registration_requires_verification = False
auth.settings.registration_requires_approval = False
auth.settings.reset_password_requires_verification = True

## if you need to use OpenID, Facebook, MySpace, Twitter, Linkedin, etc.
## register with janrain.com, write your domain:api_key in private/janrain.key
from gluon.contrib.login_methods.rpx_account import use_janrain
use_janrain(auth, filename='private/janrain.key')

#########################################################################
## Define your tables below (or better in another model file) for example
##
## >>> db.define_table('mytable',Field('myfield','string'))
##
## Fields can be 'string','text','password','integer','double','boolean'
##       'date','time','datetime','blob','upload', 'reference TABLENAME'
## There is an implicit 'id integer autoincrement' field
## Consult manual for more options, validators, etc.
##
## More API examples for controllers:
##
## >>> db.mytable.insert(myfield='value')
## >>> rows=db(db.mytable.myfield=='value').select(db.mytable.ALL)
## >>> for row in rows: print row.id, row.myfield
#########################################################################

## after defining tables, uncomment below to enable auditing
# auth.enable_record_versioning(db)

db.define_table('student',
    db.Field('student_id',requires=IS_IN_DB(db,'auth_user.id','auth_user.first_name')),
    db.Field('name','string'),
    db.Field('age','integer'),
    db.Field('gender','string',requires=IS_IN_SET(['Male','Female'])),
    db.Field('dob','datetime'),
    db.Field('image','upload'),
    db.Field('address1','text'),
    db.Field('address2','text'),
    db.Field('address3','text'),
    db.Field('contact','string'),
    db.Field('email','string',requires=IS_EMAIL()),
    db.Field('cgpa','double'),
    #    db.Field('high_school_marks','double'),
    #    db.Field('intermediate_marks','double'),
    db.Field('stream','string'),
    db.Field('def_temp','string',default='1'))

#db.define_table('student_table',
 #   db.Field('student_id',requires=IS_IN_DB(db,'auth_user.id','auth_user.first_name')),
  #  db.Field('table_id',requires=IS_IN_DB(db,'student.id','student.id')))
    
db.define_table('course',
    db.Field('student_id',requires=IS_IN_DB(db,'auth_user.id','auth_user.first_name')),
    db.Field('student_name','string'),
    db.Field('name','string'))

#db.define_table('course_table',
 #   db.Field('table_id',requires=IS_IN_DB(db,'course.id','course.id')))

db.define_table('project',
    db.Field('student_name','string'),
    db.Field('student_id',requires=IS_IN_DB(db,'auth_user.id','auth_user.first_name')),
    db.Field('name','string'),
    db.Field('detail','text'))

#db.define_table('project_table',
 #   db.Field('student_id',requires=IS_IN_DB(db,'auth_user.id','auth_user.first_name')),
  #  db.Field('table_id',requires=IS_IN_DB(db,'project.id','project.id')))

db.define_table('extra',
    db.Field('student_name','string'),
    db.Field('student_id',requires=IS_IN_DB(db,'auth_user.id','auth_user.first_name')),
    db.Field('title','string'),
    db.Field('info','text'))

#db.define_table('extra_table',
 #   db.Field('table_id',requires=IS_IN_DB(db,'extra.id','extra.id')))

db.define_table('activity',
    db.Field('student_name','string'),
    db.Field('student_id',requires=IS_IN_DB(db,'auth_user.id','auth_user.first_name')),
    db.Field('title','string'),
    db.Field('detail','text'))

#db.define_table('activity_table',
 #   db.Field('table_id',requires=IS_IN_DB(db,'activity.id','activity.id')))

#db.define_table('image',
#	db.Field('student_id',requires=IS_IN_DB(db,'auth_user.id','auth_user.first_name')),
#	db.Field('img','upload'))

db.define_table('messages',
	db.Field('receiver_id',requires=IS_IN_DB(db,'auth_user.id','auth_user.first_name')),
	db.Field('student_id',requires=IS_IN_DB(db,'auth_user.id','auth_user.first_name')),
	db.Field('body','text'))

#db.define_table('message_table',
#	db.Field('student_id',requires=IS_IN_DB(db,'auth_user.id','auth_user.first_name')),
#	db.Field('table_id',requires=IS_IN_DB(db,'messages.id','messages.id')))

db.define_table('institution',
    	db.Field('student_name','string'),
	db.Field('student_id',requires=IS_IN_DB(db,'auth_user.id','auth_user.first_name')),
	db.Field('title','string'),
	db.Field('name','string'),
	db.Field('grade','double'))

db.define_table('coment',
	db.Field('body','string'),
	db.Field('sender_id',requires=IS_IN_DB(db,'auth_user.id','auth_user.id')),
	db.Field('likes','integer'),
	db.Field('receiver',requires=IS_IN_DB(db,'auth_user.id','auth_user.id')))

db.define_table('liked_comment',
	db.Field('user_id',requires=IS_IN_DB(db,'auth_user.id','auth_user.id')),
	db.Field('comment_id',requires=IS_IN_DB(db,'comment.id','comment.id')),
	db.Field('liked','integer'))

db.define_table('work_expr',
	db.Field('student_id',requires=IS_IN_DB(db,'auth_user.id','auth_user.first_name')),
    	db.Field('student_name','string'),
	db.Field('name','string'),
	db.Field('as_post','string'),
	db.Field('type_of',requires=IS_IN_SET(['intern','employ'])),
	db.Field('start_time','datetime'),
	db.Field('end_time','datetime'),
	db.Field('is_left',requires=IS_IN_SET(['Yes','No'])))

db.define_table('company',
	db.Field('company_id',requires=IS_IN_DB(db,'company.id','company.id')),
	db.Field('name','string'),
	db.Field('about','text'),
	db.Field('web_link','string'))

db.define_table('vacancy',
	db.Field('company_name','string'),
	db.Field('company_id',requires=IS_IN_DB(db,'company.id','company.id')),
	db.Field('post_com','string'))

db.define_table('req_com',
	db.Field('company_name','string'),
	db.Field('company_id',requires=IS_IN_DB(db,'company.id','company.id')),
	db.Field('vacancy_id',requires=IS_IN_DB(db,'vacancy.id','vacancy.id')),
	db.Field('req_name','string'),
	db.Field('req_det','text'))

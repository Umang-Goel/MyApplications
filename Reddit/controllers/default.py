# -*- coding: utf-8 -*-
# this file is released under public domain and you can use without limitations

#########################################################################
## This is a samples controller
## - index is the default action of any application
## - user is required for authentication and authorization
## - download is for downloading files uploaded in the db (does streaming)
## - call exposes all registered services (none by default)
#########################################################################
import datetime

def index():
    """
    example action using the internationalization operator T and flash
    rendered by views/default/index.html or views/generic.html

    if you need a simple wiki simple replace the two lines below with:
    return auth.wiki()
    """
    redirect(URL(r=request,f='no_catg'))
    #query=db(db.category.name=='New').select(db.category.id)
    #redirect(URL(r=request, f='first_page',args=[int(query[0].id)]))

@auth.requires_login()
def login_to_account():
	ar=db((db.auth_membership.user_id==auth.user_id) & (db.auth_group.id==db.auth_membership.group_id)).select(db.auth_group.role)
	if(len(ar)==0):
		redirect(URL(r=request,f='user'))
	elif(len(ar)==1):
		x=db(db.auth_group.role=='normal').select(db.auth_group.id)
		db.auth_membership.insert(user_id=auth.user_id,group_id=x[0]['id'])
    		query=db(db.category.name=='New').select(db.category.id)
    		redirect(URL(r=request, f='login_normal',args=[int(query[0].id)]))
	elif(ar[1]['role']=='normal'):
    		query=db(db.category.name=='New').select(db.category.id)
    		redirect(URL(r=request, f='login_normal',args=[int(query[0].id)]))
	elif(ar[1]['role']=='admin'):
		session.flash=T('Welcome Admin')
    		query=db(db.category.name=='New').select(db.category.id)
    		redirect(URL(r=request, f='login_admin',args=[int(query[0].id)]))

def login_normal():
	query=int(request.args(0))
	disp=db((db.news.user_id==auth.user_id) & (db.news.category_id==query)).select(db.news.id,db.news.heading,db.news.url,db.news.category_id,db.news.ntype,db.news.rating,db.news.pres_time,orderby=~db.news.rating)
	has_liked=db((db.news.category_id==query) & (db.rating.news_id==db.news.id)).select(db.rating.ALL)
	q_comment=db((db.news.category_id==query) & (db.comments.news_id==db.news.id)).select(db.comments.ALL)
	catg=db(db.category.id>0).select(db.category.name,db.category.id)
	pres_catg=db(db.category.id==query).select(db.category.name)
	return dict(disp=disp,q_comment=q_comment,catg=catg,pres_catg=pres_catg,query=query,has_liked=has_liked)	

def login_admin():
	query=int(request.args(0))
	disp=db(db.news.category_id==query).select(db.news.id,db.news.user_name,db.news.heading,db.news.url,db.news.category_id,db.news.ntype,db.news.rating,db.news.pres_time,orderby=~db.news.rating)
	has_liked=db((db.news.category_id==query) & (db.rating.news_id==db.news.id)).select(db.rating.ALL)
	q_comment=db((db.news.category_id==query) & (db.comments.news_id==db.news.id)).select(db.comments.ALL)
	catg=db(db.category.id>0).select(db.category.name,db.category.id)
	pres_catg=db(db.category.id==query).select(db.category.name)
	return dict(disp=disp,q_comment=q_comment,catg=catg,pres_catg=pres_catg,query=query,has_liked=has_liked)	

def promote_admin():
	catg=int(request.args(0))
	form=SQLFORM.factory(
	 db.Field('user_id','int',label="Choose User",requires=IS_IN_DB(db,'auth_user.id','auth_user.first_name')),
	 formstyle='divs',
	 buttons=[],)
   	form[0].insert(1,DIV(INPUT(_type='submit',_value='ADD')))
	if form.accepts(request.vars,session):
		query=db(db.auth_group.role=="normal").select(db.auth_group.id)
		cond=db((db.auth_membership.user_id==form.vars.user_id) & (db.auth_membership.group_id==query[0].id)).select(db.auth_membership.ALL)
		if(len(cond)==0):
			session.flash=T('Already Admin')
			redirect(URL(r=request,f='login_admin',args=[(int)(catg)]))
		if(len(cond)!=0):
			grp=db(db.auth_group.role=="admin").select(db.auth_group.id)
			db((db.auth_membership.user_id==form.vars.user_id) & (db.auth_membership.group_id==query[0].id)).delete()
			db.auth_membership.insert(user_id=form.vars.user_id,group_id=grp[0].id)
			session.flash=T('User Promoted To Admin')
			redirect(URL(r=request,f='login_admin',args=[(int)(catg)]))
    	elif form.errors:
       		 response.flash='Error Occured'
	return dict(form=form)

def demote():
	catg=int(request.args(0))
	query=db(db.auth_group.role=="admin").select(db.auth_group.id)
	grp=db(db.auth_group.role=="normal").select(db.auth_group.id)
	db((db.auth_membership.user_id==auth.user_id) & (db.auth_membership.group_id==query[0].id)).delete()
	db.auth_membership.insert(user_id=auth.user_id,group_id=grp[0].id)
	session.flash=T('User Changed')
	redirect(URL(r=request,f='login_normal',args=[int(catg)]))

def add_category():
	catg=int(request.args(0))
	form=SQLFORM(db.category,submit_button="Add",labels={'name':'Enter Category'})
	if form.process().accepted:
		session.flash=T('Category Added')
		redirect(URL(r=request,f='login_admin',args=[(int)(catg)]))
    	elif form.errors:
       		 response.flash='Some Error Occured Please Refresh'
	return dict(form=form)

@auth.requires_login()
def edit_news_admin():
	news_id=int(request.args(0))
	catg=int(request.args(1))
	flag=int(request.args(2))
	form=SQLFORM.factory(
	 db.Field('new_heading','string',label="Enter Heading"),
	 db.Field('new_url','string',label="Enter URL",requires=IS_URL()),
	 db.Field('new_type','string',label="Enter Type",requires=IS_IN_SET(["Text","Video"])),
	 formstyle='divs',
	 buttons=[],)
	form[0].insert(3,DIV(INPUT(_type='submit',_value='Edit IT')))
   	if form.accepts(request.vars,session):
		# tmp_edit(form.vars.new_heading,form.vars.new_url,form.vars.new_type,news_id,catg,flag)
		db(db.news.id==news_id).update(heading=form.vars.new_heading,url=form.vars.new_url,ntype=form.vars.new_type)
		#db(db.rating.news_id==news_id).delete()
		redirect(URL(r=request,f='login_admin',args=[(int)(catg)]))
    	elif form.errors:
       		 response.flash='Error Occured'
	return dict(form=form)

@auth.requires_login()
def delete_news_admin():
	news_id=int(request.args(0))
	catg=int(request.args(1))
	flag=int(request.args(2))
	db(db.news.id==news_id).delete()
	session.flash=T('Post Deleted Successfully')
	redirect(URL(r=request,f='login_admin',args=[(int)(catg)]))

def first_page():
	query=int(request.args(0))
	disp=db(db.news.category_id==query).select(db.news.heading,db.news.url,db.news.rating,db.news.ntype,db.news.id,db.news.pres_time,db.news.user_name,orderby=~db.news.rating)
	has_liked=db((db.news.category_id==query) & (db.rating.news_id==db.news.id)).select(db.rating.ALL)
	q_comment=db((db.news.category_id==query) & (db.comments.news_id==db.news.id)).select(db.comments.ALL)
	catg=db(db.category.id>0).select(db.category.name,db.category.id)
	pres_catg=db(db.category.id==query).select(db.category.name)
	disp=sorted(disp,key=lambda a:-a['rating'])
	"""
	form=SQLFORM.factory(
	 db.Field('comm_body','string',label=""),
	 formstyle='divs',
	 buttons=[],)
   	form[0].insert(1,DIV(INPUT(_type='submit',_value='Post')))
   	if form.accepts(request.vars,session):
        	 insert_comment(form.vars.comm_body,auth.user_id,query)
    	elif form.errors:
        	 response.flash='Some Error Occured Please Refresh'
    	"""
	return dict(query=query,disp=disp,q_comment=q_comment,catg=catg,pres_catg=pres_catg,has_liked=has_liked)

def no_catg():
	disp=db(db.news.id>0).select(db.news.ALL,orderby=~db.news.rating)
	q_comment=db(db.comments.id>0).select(db.comments.ALL)
	catg=db(db.category.id>0).select(db.category.name,db.category.id)
	return dict(disp=disp,q_comment=q_comment,catg=catg)

def latest():
	disp=db(db.news.id>0).select(db.news.ALL,orderby=~db.news.pres_time)
	q_comment=db(db.comments.id>0).select(db.comments.body,db.comments.commentor)
	catg=db(db.category.id>0).select(db.category.name,db.category.id)
	return dict(disp=disp,q_comment=q_comment,catg=catg)

@auth.requires_login()
def add_news():
	catg=int(request.args(0))
	flag=int(request.args(1))
	name=db(db.auth_user.id==auth.user_id).select(db.auth_user.first_name,db.auth_user.last_name)
	db.news.pres_time.default=datetime.datetime.now().ctime()
	db.news.pres_time.readable=False
	db.news.pres_time.writable=False
	db.news.category_id.default=catg
	db.news.category_id.readable=False
	db.news.category_id.writable=False
	db.news.user_id.default=auth.user_id
	db.news.user_id.writable=False
	db.news.user_id.readable=False
	db.news.rating.default=100
	db.news.rating.writable=False
	db.news.rating.readable=False
	db.news.user_name.default=name[0].first_name+" "+name[0].last_name
	db.news.user_name.readable=False
	db.news.user_name.writable=False
	form=SQLFORM(db.news,submit_button="Post",labels={'ntype':'Post Type'})
	if form.process().accepted:
		if(flag==0):
			session.flash=T('Post Added')
	        	redirect(URL(r=request, f='first_page',args=[int(catg)]))
		if(flag==1) :
			session.flash=T('Post Added')
	        	redirect(URL(r=request, f='login_normal',args=[int(catg)]))
		if(flag==2) :
			session.flash=T('Post Added')
	        	redirect(URL(r=request, f='login_admin',args=[int(catg)]))
		#redirect(URL(r=request,f='first_page?query=%s' % catg))
	elif form.errors:
		response.flash="Error posting it"
	return dict(form=form)

@auth.requires_login()
def like():
	news_id=int(request.args(0))
	catg=int(request.args(1))
	flag=int(request.args(2))
	ar=db(db.news.id==news_id).select(db.news.rating)
	query=db((db.rating.news_id==news_id) & (db.rating.rater_id==auth.user_id)).select(db.rating.liked,db.rating.disliked)
	if(len(query)==0):
		db(db.news.id==news_id).update(rating=ar[0].rating+5)
		db.rating.insert(news_id=news_id,rater_id=auth.user_id,liked=1,disliked=0)
		session.flash=T('You Voted Up')
	if(len(query)!=0):
		if(int(query[0].liked)==1):
			db(db.news.id==news_id).update(rating=ar[0].rating-5)
			db((db.rating.news_id==news_id) & (db.rating.rater_id==auth.user_id)).update(liked=0)
			session.flash=T('Your Vote Cancelled')
		if(int(query[0].liked)==0 and int(query[0].disliked)==0):
			db(db.news.id==news_id).update(rating=ar[0].rating+5)
			db((db.rating.news_id==news_id) & (db.rating.rater_id==auth.user_id)).update(liked=1)
			session.flash=T('You Voted Up')
	if(flag==0):
		redirect(URL(r=request, f='first_page',args=[int(catg)]))
	elif(flag==1) :
		redirect(URL(r=request,f='login_normal',args=[(int)(catg)]))
	elif(flag==2) :
		redirect(URL(r=request,f='login_admin',args=[(int)(catg)]))


@auth.requires_login()
def dislike():
	news_id=int(request.args(0))
	catg=int(request.args(1))
	flag=int(request.args(2))
	ar=db(db.news.id==news_id).select(db.news.rating)
	query=db((db.rating.news_id==news_id) & (db.rating.rater_id==auth.user_id)).select(db.rating.disliked,db.rating.liked)
	if(len(query)==0):
		db(db.news.id==news_id).update(rating=ar[0].rating-3)
		db.rating.insert(news_id=news_id,rater_id=auth.user_id,liked=0,disliked=1)
		session.flash=T('You Voted Down')
	if(len(query)!=0):
		if(int(query[0].disliked)==1):
			db(db.news.id==news_id).update(rating=ar[0].rating+3)
			db((db.rating.news_id==news_id) & (db.rating.rater_id==auth.user_id)).update(disliked=0)
			session.flash=T('You Vote Cancelled')
		if(int(query[0].disliked)==0 and int(query[0].liked)==0):
			db(db.news.id==news_id).update(rating=ar[0].rating-3)
			db((db.rating.news_id==news_id) & (db.rating.rater_id==auth.user_id)).update(disliked=1)
			session.flash=T('You Voted Down')
	if(flag==0):
		redirect(URL(r=request,f='first_page',args=[(int)(catg)]))
	elif(flag==1) :
		redirect(URL(r=request,f='login_normal',args=[(int)(catg)]))
	elif(flag==2) :
		redirect(URL(r=request,f='login_admin',args=[(int)(catg)]))
	#return dict(query=query)

@auth.requires_login()
def edit_news():
	news_id=int(request.args(0))
	catg=int(request.args(1))
	flag=int(request.args(2))
	query=db((db.news.id==news_id) & (db.news.user_id==auth.user_id)).select(db.news.heading)
	if(len(query)==0):
		redirect(URL(r=request,f='first_page',args=[(int)(catg)]))
	else :
		form=SQLFORM.factory(
		 db.Field('new_heading','string',label="Enter Heading"),
		 db.Field('new_url','string',label="Enter URL",requires=IS_URL()),
		 db.Field('new_type','string',label="Enter Type",requires=IS_IN_SET(["Text","Video"])),
		 formstyle='divs',
		 buttons=[],)
   		form[0].insert(3,DIV(INPUT(_type='submit',_value='Edit IT')))
	   	if form.accepts(request.vars,session):
        		 tmp_edit(form.vars.new_heading,form.vars.new_url,form.vars.new_type,news_id,catg,flag)
	    	elif form.errors:
        		 response.flash='Some Error Occured Please Refresh'
		return dict(form=form)

@auth.requires_login()
def tmp_edit(new_heading,new_url,new_type,news_id,catg,flag):
	db(db.news.id==news_id).update(heading=new_heading,url=new_url,ntype=new_type)
	#db(db.rating.news_id==news_id).delete()
	if(flag==0):
		session.flash=T('Post Edited Successfully')
		redirect(URL(r=request,f='first_page',args=[(int)(catg)]))
	else :
		session.flash=T('Post Edited Successfully')
		redirect(URL(r=request,f='login_normal',args=[(int)(catg)]))
	

@auth.requires_login()
def delete_news():
	news_id=int(request.args(0))
	catg=int(request.args(1))
	flag=int(request.args(2))
	query=db((db.news.id==news_id) & (db.news.user_id==auth.user_id)).select(db.news.id)
	if(len(query)>0):
		db((db.news.id==news_id) & (db.news.user_id==auth.user_id)).delete()
		db(db.rating.news_id==news_id).delete()
		db(db.comments.news_id==news_id).delete()
		session.flash=T('Post Deleted Successfully')
	if(flag==0):
		redirect(URL(r=request,f='first_page',args=[(int)(catg)]))
	else :
		redirect(URL(r=request,f='login_normal',args=[(int)(catg)]))

def delete_catg():
	catg_id=int(request.args(0))
	form=SQLFORM.factory(
	 db.Field('catg_id','int',label="Choose Category",requires=IS_IN_DB(db,'category.id','category.name')),
	 formstyle='divs',
	 buttons=[],)
   	form[0].insert(1,DIV(INPUT(_type='submit',_value='Delete It')))
	if form.accepts(request.vars,session):
		query=db(db.news.category_id==form.vars.catg_id).select(db.news.id)
		q2=db(db.category.name=='New').select(db.category.id)
		if(int(form.vars.catg_id)==int(q2[0].id)):
			session.flash=T('Category Reserved Cant be Deleted')
			redirect(URL(r=request,f='login_admin',args=[(int)(catg_id)]))

		for x in query:
			db(db.rating.news_id==x.id).delete()
			db(db.news.id==x.id).delete()
		db(db.category.id==form.vars.catg_id).delete()
		session.flash=T('Category Deleted')
		query=db(db.category.name=='New').select(db.category.id)
		redirect(URL(r=request,f='login_admin',args=[(int)(query[0].id)]))
		#redirect(URL(r=request, f='no_catg'))
		#tmp_edit(form.vars.new_heading,form.vars.new_url,form.vars.new_type,news_id,catg,flag)
  	elif form.errors:
       		 response.flash='Some Error Occured Please Refresh'
	return dict(form=form)

@auth.requires_login()
def insert_comment():
	catg_id=int(request.args(1))
	news_id1=(int)(request.args(0))
	flag=int(request.args(2))
	db.comments.comm_time.default=datetime.datetime.now().ctime()
	db.comments.comm_time.readable=False
	db.comments.comm_time.writable=False
	db.comments.commentor.default=auth.user_id
	db.comments.commentor.readable=False
	db.comments.commentor.writable=False
	db.comments.news_id.default=news_id1
	db.comments.news_id.readable=False
	db.comments.news_id.writable=False
	form=SQLFORM(db.comments,submit_button="Comment",labels={'body':'Your Comment'})
	if form.process().accepted:
		if(flag==0):
			session.flash=T('Comment Inserted')
	        	redirect(URL(r=request, f='first_page',args=[int(catg_id)]))
		else :
			session.flash=T('Comment Inserted')
			redirect(URL(r=request, f='login_to_account'))
		#redirect(URL(r=request,f='first_page?query=%s' % catg))
	elif form.errors:
		response.flash="Error posting it"
	return dict(form=form)

def delete_user():
	catg_id=int(request.args(0))
	form=SQLFORM.factory(
	 db.Field('user_id','int',label="Choose User",requires=IS_IN_DB(db,'auth_user.id','auth_user.first_name')),
	 formstyle='divs',
	 buttons=[],)
   	form[0].insert(1,DIV(INPUT(_type='submit',_value='Delete')))
	if form.accepts(request.vars,session):
		query=db(db.rating.rater_id==form.vars.user_id).select(db.rating.ALL)
		for y in query:
			if(y.liked==1):
				q2=db(db.news.id==y.news_id).select(db.news.rating)
				db(db.news.id==y.news_id).update(rating=q2[0].rating-5)
			if(y.disliked==1):
				q2=db(db.news.id==y.news_id).select(db.news.rating)
				db(db.news.id==y.news_id).update(rating=q2[0].rating+3)
		query=db(db.news.user_id==form.vars.user_id).select(db.news.ALL)
		for x in query:
			db(db.comments.news_id==x.id).delete()
		db(db.news.user_id==form.vars.user_id).delete()
		db(db.auth_membership.user_id==form.vars.user_id).delete()
		db(db.auth_user.id==form.vars.user_id).delete()
		session.flash=T('User Deleted')
		redirect(URL(r=request, f='login_admin',args=[int(catg_id)]))
	elif form.errors:
		response.flash="Error posting it"
	return dict(form=form)

def user():
    """
    exposes:
    http://..../[app]/default/user/login
    http://..../[app]/default/user/logout
    http://..../[app]/default/user/register
    http://..../[app]/default/user/profile
    http://..../[app]/default/user/retrieve_password
    http://..../[app]/default/user/change_password
    use @auth.requires_login()
        @auth.requires_membership('group name')
        @auth.requires_permission('read','table name',record_id)
    to decorate functions that need access control
    """
    return dict(form=auth())


def download():
    """
    allows downloading of uploaded files
    http://..../[app]/default/download/[filename]
    """
    return response.download(request, db)


def call():
    """
    exposes services. for example:
    http://..../[app]/default/call/jsonrpc
    decorate with @services.jsonrpc the functions to expose
    supports xml, json, xmlrpc, jsonrpc, amfrpc, rss, csv
    """
    return service()


@auth.requires_signature()
def data():
    """
    http://..../[app]/default/data/tables
    http://..../[app]/default/data/create/[table]
    http://..../[app]/default/data/read/[table]/[id]
    http://..../[app]/default/data/update/[table]/[id]
    http://..../[app]/default/data/delete/[table]/[id]
    http://..../[app]/default/data/select/[table]
    http://..../[app]/default/data/search/[table]
    but URLs must be signed, i.e. linked with
      A('table',_href=URL('data/tables',user_signature=True))
    or with the signed load operator
      LOAD('default','data.load',args='tables',ajax=True,user_signature=True)
    """
    return dict(form=crud())

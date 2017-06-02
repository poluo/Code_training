# -*- coding: utf-8 -*-
import scrapy
import re
import json


class UserSpider(scrapy.Spider):
    name = "user"
    allowed_domains = ["zhihu.com"]
    count = {}
    def start_requests(self,urls=None):
        if not urls:
            urls = self.settings.getlist('URL')

        for one in urls:
            yield scrapy.Request(url=one, callback=self.parse)


    def parse(self, response):
        text = response.text.replace('&quot;', '"')
        # self.logger.info(text)
        next_url = 'https:' + re.findall('"next":"http://.*desktop=True', text)[0].split(':')[2].replace('amp;','')
        self.logger.info(next_url)
        yield scrapy.Request(url=next_url, meta={'referer': response.url}, callback=self.parse_activities)

    def parse_activities(self, response):
        try:
            data = json.loads(response.text)
            name = data['data'][0]['actor']['name']
            if name not in self.count:
                self.count[name] = 0
                if len(self.count) > 100:
                    self.logger.warning('more than 100 user')
                    scrapy.exceptions.CloseSpider('more than 100 user')
            else:
                self.count[name] += 1
            with open('{}_{}.json'.format(name,self.count[name]),'w') as fobj:
                json.dump(data,fobj)
            self.process_data(data['data'])
            urls = self.process_urls(data['data'])
            self.logger.info(urls)
            for one in urls:
                yield scrapy.Request(url=one,callback=self.parse)
        except Exception as e:
            self.logger.info(e)
            self.logger.info(response.text)
        if not data['paging']['is_end']:
            next_url = data['paging']['next']
            self.logger.info('next_page {}'.format(next_url))
            yield scrapy.Request(url=next_url, meta={'referer': response.url}, callback=self.parse_activities)
        else:
            self.logger.info('Arrived end page')

    def process_urls(self,data):
        urls = set()
        for one in data:
            if one['target']['type'] == 'answer':
                tmp = one['target']['author']['url_token']
                if tmp:
                    tmp = ''.join(['https://www.zhihu.com/people/',tmp,'/activities'])
                    urls.add(tmp)
                tmp = one['target']['question']['author']['url_token']
                if tmp:
                    tmp = ''.join(['https://www.zhihu.com/people/',tmp,'/activities'])
                    urls.add(tmp)
            else:
                if one['target']['type'] == 'question':
                    tmp = one['target']['author']['url_token']
                    if tmp:
                        tmp = ''.join(['https://www.zhihu.com/people/',tmp,'/activities'])
                        urls.add(tmp)
                else:
                    pass
        return urls
     def process_data(self,data):
	     for one in data['data']:
            #关注了问题
            if one['verb'] == 'QUESTION_FOLLOW':
                res={'type':'QUESTION_FOLLOW','created_time':one['created_time'],'questions_id':one['target']['id'],'title':one['target']['title']}
                # print(res)
            #回答了问题
            elif one['verb'] == 'ANSWER_CREATE':
                res={'type':'ANSWER_CREATE','created_time':one['created_time'],'questions_id':one['target']['id'],'content':one['target']['content'],'title':one['target']['question']['title']}
                # print(res)
            #赞同了回答
            elif one['verb'] == 'ANSWER_VOTE_UP':
                res={'type':'ANSWER_VOTE_UP','created_time':one['created_time'],'questions_id':one['target']['question']['id'],'title':one['target']['question']['title'],'answer_id':str(one['target']['id']) + one['target']['url'] }
                # print(res)
            #收藏了回答
            elif one['verb'] == 'MEMBER_COLLECT_ANSWER':
                res={'type':'MEMBER_COLLECT_ANSWER','created_time':one['created_time'],'questions_id':one['target']['question']['id'],'title':one['target']['question']['title'],'answer_id':str(one['target']['id']) + one['target']['url'] }
                # print(res)
            #赞了文章
            elif one['verb'] == 'MEMBER_VOTEUP_ARTICLE':
                res={'type':'MEMBER_VOTEUP_ARTICLE','created_time':one['created_time'],'title':one['target']['title'],'articles_id':str(one['target']['id']) + one['target']['url'],'author':one['target']['author']['name']}
                # print(res)
            #关注了圆桌
            elif one['verb'] == 'MEMBER_FOLLOW_ROUNDTABLE':
                 res={'type':'MEMBER_FOLLOW_ROUNDTABLE','created_time':one['created_time'],'title':one['target']['name'],'url':str(one['target']['id']) + one['target']['url']}
                # print(res)
            #关注了话题
            elif one['verb'] == 'TOPIC_FOLLOW':
                res={'type':'TOPIC_FOLLOW','created_time':one['created_time'],'title':one['target']['name'],'url':str(one['target']['id']) + one['target']['url']}
                # print(res)
            #关注了专栏
            elif one['verb'] == 'MEMBER_FOLLOW_COLUMN':
                res={'type':'MEMBER_FOLLOW_COLUMN','created_time':one['created_time'],'title':one['target']['title'],'url':str(one['target']['id']) + one['target']['url']}
                # print(res)
            #收藏了文章
            elif one['verb'] == 'MEMBER_COLLECT_ARTICLE':
                res={'type':'MEMBER_COLLECT_ARTICLE','created_time':one['created_time'],'title':one['target']['title'],'articles_id':str(one['target']['id']) + one['target']['url'],'author':one['target']['author']['name']}
                # print(res)
            else:
                pass
     
if __name__ == '__main__':
    from scrapy.cmdline import execute

    execute()

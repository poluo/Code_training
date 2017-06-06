import json
from os import listdir
from os.path import isfile, join
from datetime import datetime
import jieba
from wordcloud import WordCloud

def print_info(one):
    if one['type'] == 'QUESTION_FOLLOW':
        print('{} 关注了问题 {} 问题id是 {}'.format(convert_time(one['created_time']),one['title'],one['questions_id']))
    #回答了问题
    elif one['type'] == 'ANSWER_CREATE':
        print('{} 回答了问题 {}问题id是 {}'.format(convert_time(one['created_time']),one['title'],one['questions_id']))
    #赞同了回答
    elif one['type'] == 'ANSWER_VOTE_UP':
        print('{} 赞同了回答 {} 问题id是 {} 回答id是 {} '.format(convert_time(one['created_time']),one['title'],one['questions_id'],one['answer_id']))
    #收藏了回答
    elif one['type'] == 'MEMBER_COLLECT_ANSWER':
        print('{} 收藏了回答 {} 问题id是 {} 回答id是{} '.format(convert_time(one['created_time']),one['title'],one['questions_id'],one['answer_id']))
    #赞了文章
    elif one['type'] == 'MEMBER_VOTEUP_ARTICLE':
        print('{} 赞了文章 {} id是 {} 作者是 {} '.format(convert_time(one['created_time']),one['title'],one['articles_id'],one['author']))
    #关注了圆桌
    elif one['type'] == 'MEMBER_FOLLOW_ROUNDTABLE':
        print('{} 关注了圆桌 {} 连接是 {} '.format(convert_time(one['created_time']),one['title'],one['url']))
    #关注了话题
    elif one['type'] == 'TOPIC_FOLLOW':
        print('{} 关注了话题 {} 连接是 {} '.format(convert_time(one['created_time']),one['title'],one['url']))
    #关注了专栏
    elif one['type'] == 'MEMBER_FOLLOW_COLUMN':
        print('{} 关注了专栏 {} 连接是 {} '.format(convert_time(one['created_time']),one['title'],one['url']))
        # print(res)
    #收藏了文章
    elif one['type'] == 'MEMBER_COLLECT_ARTICLE':
        print('{} 赞了文章 {} id是 {} 作者是{} '.format(convert_time(one['created_time']),one['title'],one['articles_id'],one['author']))
    else:
        pass

def convert_time(t):
    return (datetime.strftime(datetime.fromtimestamp(t),'%Y年%m月%d日%H时%M分'))

def convert(name,action):
    print(name)
    title_set = set()
    word_dict = {}
    for one in action:
        #关注了问题
        if not one:
            continue
        title_set.add(one['title'])
        # print_info(one)
    for title in title_set:
        tmp = jieba.cut(title,cut_all=True)
        for one in tmp:
            if not one:
                continue
            if one in word_dict:
                word_dict[one] += 1
            else:
                word_dict[one] = 1
    d = WordCloud(font_path = './simfang.ttf').generate_from_frequencies(word_dict)
    import matplotlib.pyplot as plt
    plt.imsave('tmp.png',d)
    #plt.axis("off")
	
onlyfiles = [ f for f in listdir('./data') if isfile(join('./data',f)) ]
name={}
for file in onlyfiles:
    if '.json' not in file:
        break
    with open(join('./data',file),'r',encoding='utf8') as fobj:
        for one in fobj:
            data = json.loads(one)
            try:
                if data['name'] not in name:
                    name[data['name']] = []
                    name[data['name']].append(data['action'])
                else:
                    name[data['name']].append(data['action'])
            except KeyError:
                pass

for k,v in name.items():
    convert(k,v)
    break


            

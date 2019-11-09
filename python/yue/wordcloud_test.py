from wordcloud import WordCloud

text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."

wordcloud = WordCloud(background_color="white", width=800,height=800).generate(text)
wordcloud.to_file("./test.png")

# 
# https://qiita.com/567000/items/5f4ea1e8268109ffc3b7

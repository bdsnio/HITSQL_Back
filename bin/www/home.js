window.onload = function() {
    //获取用户注册/登录时的用户名，显示为用户名+的空间
    var username = localStorage.getItem('username');
    if (username) {
        document.getElementById('myspaceBtn').innerHTML = '<strong>' + username + '</strong> 的空间';
    }
    else{
        document.getElementById('myspaceBtn').textContent = '我的空间';
    }

    // 获取当前时间并格式化为"小时:分钟"格式
    var now = new Date();
    var hours = String(now.getHours()).padStart(2, '0'); // 确保小时是两位数
    var minutes = String(now.getMinutes()).padStart(2, '0'); // 确保分钟是两位数
    var formattedDate = hours + ':' + minutes; // 拼接时间格式

    // 获取post-time元素并设置时间
    document.querySelector('.post-time').textContent = '发布于 ' + formattedDate;
};

document.getElementById('publishBtn').addEventListener('click', function() {
    window.location.href = 'publish.html';
});

document.getElementById('myspaceBtn').addEventListener('click', function() {
    window.location.href = 'myspace.html';
});

// 添加好友按钮点击事件
function FriendButtonClick(event) {
    var friendBtn = event.target; // 获取点击的按钮元素

    // 检查按钮是否已经被点击过
    if (friendBtn.innerHTML === '加为好友') {
        // 改变按钮文本为“已成为好友”
        friendBtn.innerHTML = '已成为好友';

        // 修改按钮样式为浅蓝色背景
        friendBtn.style.backgroundColor = '#f0f0f0'; // 浅蓝色背景
        friendBtn.style.color = '#333'; // 黑色文字，可以按需调整颜色
        friendBtn.style.fontWeight = 'normal'; // 字体改为非加粗
    } else {
        // 如果按钮文本已经是“已成为好友”，则可以在这里添加额外逻辑
        // 例如，不做任何操作或提示用户已经是好友
        alert('已经是好友关系');
    }
}

// 添加好友按钮
document.querySelector('.friend-btn').addEventListener('click',FriendButtonClick);

// 点赞按钮点击事件
function LikeButtonClick() {
    // 检查是否已经点赞
    var isLiked = this.getAttribute('data-liked') === 'true'; 

    // 根据当前状态执行操作
    if (isLiked) {
        // 如果已经点赞，取消点赞
        this.style.backgroundColor = 'white'; // 恢复背景色为白色
        this.setAttribute('data-liked', 'false'); // 更新点赞状态
    } else {
        // 如果未点赞，执行点赞操作
        this.style.backgroundColor = '#4a77d4'; // 设置背景色为浅蓝色
        this.setAttribute('data-liked', 'true'); // 更新点赞状态
    }
}

// 点赞按钮
document.querySelector('.like-btn').addEventListener('click', LikeButtonClick);

// 评论按钮点击事件
function CommentButtonClick(event) {
    // 使用event.target确保能正确获取点击的按钮
    var commentBtn = event.target;

    // 检查点击的是否为评论按钮
    if (commentBtn.classList.contains('comment-btn')) {
        // 查找评论按钮所在的.post元素
        var postElement = commentBtn.closest('.post');

        // 获取post元素中的comments-content的id
        var commentsContentId = postElement ? postElement.querySelector('.comments-content').id : null;
    }

    var post_choose = document.querySelector('.post');
    var commentsSection_choose = post_choose.querySelector('.comments-section');

    var comment = prompt('请输入你的评论：', '');
    if (comment === null) {
        // 用户点击了取消，直接退出函数
        return;
    } else if (comment.trim()) { // 检查评论是否为空或只包含空白字符
        // 将评论显示在页面上
        displayComment(commentsContentId, username, comment);
    } else {
        // 用户没有输入任何内容，弹出提示
        alert('评论不能为空！');
    }

}

// 评论按钮
document.querySelector('.comment-btn').addEventListener('click', CommentButtonClick);

// 显示评论的函数
function displayComment(commentsContentId,username, commentText) {
    var commentsElement = document.getElementById(commentsContentId);

    var newCommentElement = document.createElement('div');
    
    // 创建用户名和评论内容的元素结构
    var userElement = document.createElement('span');
    userElement.textContent = username;
    userElement.style.color = 'blue'; // 设置用户名颜色为蓝色
    userElement.style.fontWeight = 'bold'; // 设置用户名为加粗

    var commentElement = document.createElement('span');
    commentElement.textContent = " :   " + commentText;
    commentElement.style.color = 'black'; // 设置评论内容颜色为黑色

    // 将用户名和评论内容添加到新评论元素中
    newCommentElement.appendChild(userElement);
    newCommentElement.appendChild(commentElement);
    
    commentsElement.appendChild(newCommentElement); // 将新评论元素添加到评论区域
}

//删除按钮点击事件
function DeleteButtonClick(event){
    // 使用event.target确保能正确获取点击的按钮
    var deleteBtn = event.target;
    // 检查点击的是否为转发按钮
    if (deleteBtn.classList.contains('share-btn')) {
        // 查找评论按钮所在的.post元素
        var post_to_delete = deleteBtn.closest('.post');
        post_to_delete.remove();
    }
}

// 假设已经从localStorage或其他方式获取了用户名
var username = localStorage.getItem('username') || '匿名用户'; // 如果没有用户名，默认显示为“未知用户”


// 转发按钮点击事件
function ShareButtonClick(event){
    // 获取原始的.post元素
    var originalPost = document.querySelector('.post');
    // 复制原始的post元素
    var newPost = originalPost.cloneNode(true); 

     // 生成一个随机数，可以进一步确保唯一性
    var timestamp = Date.now();
    var randomNumber = Math.floor(Math.random() * 1000000);
    var uniqueNumber = Math.round(timestamp) + randomNumber;

    // 新增函数，用于在复制时把post中所有ID最后一位的数字加1
    function incrementIdLastDigit(element) {
        if (element.nodeType === Node.ELEMENT_NODE && element.id) {
            // 找到ID中最后一个数字，并加同一个随机数
            var idParts = element.id.match(/(.*?)(\d+)$/);           
            if (idParts && idParts.length === 3) {
                var newId = idParts[1] + uniqueNumber;
                element.id = newId;
            }
            // 递归处理子节点
            Array.from(element.children).forEach(incrementIdLastDigit);
        }
    }
    incrementIdLastDigit(newPost); 

    // 遍历复制的元素，更新comment
    function updateComment(element) {
        if (element.nodeType === Node.ELEMENT_NODE) {
            // 清空评论内容
            if (element.id && element.id.startsWith('comments-content-')) {
                element.textContent = '';
            }
            
            //更新发布者
            if (element.classList.contains('post-username')) {
                var username = localStorage.getItem('username') || '未知用户';
                element.textContent = username;
            }

            //更新发布时间
            if (element.classList.contains('post-time')){           
                var now = new Date();
                var hours = String(now.getHours()).padStart(2, '0'); // 确保小时是两位数
                var minutes = String(now.getMinutes()).padStart(2, '0'); // 确保分钟是两位数
                var formattedDate = hours + ':' + minutes; // 拼接时间格式
                var currentTime = '发布于 ' + formattedDate; // 获取当前时间并转换为本地时间字符串
                element.textContent = currentTime;
            }

            // 递归处理子节点
            Array.from(element.children).forEach(updateComment);
        }
    }
    updateComment(newPost);

    function bindButtonsEvents(postElement) {
        // 添加好友按钮
        var friendBtn = postElement.querySelector('.friend-btn');
        if (friendBtn) {
            friendBtn.addEventListener('click', FriendButtonClick);
        }

        // 点赞按钮
        var likeBtn = postElement.querySelector('.like-btn');
        if (likeBtn) {
            likeBtn.addEventListener('click', LikeButtonClick);
        }
    
        // 评论按钮
        var commentBtn = postElement.querySelector('.comment-btn');
        if (commentBtn) {
            commentBtn.addEventListener('click', CommentButtonClick);
        }
    }

    // 绑定原始帖子按钮事件
    bindButtonsEvents(originalPost);
    // 绑定复制帖子按钮事件
    bindButtonsEvents(newPost);

    //删除添加好友按钮
    var friendbtn_new=newPost.querySelector('.friend-btn');
    if(friendbtn_new) friendbtn_new.remove();

    //点赞按钮状态初始化
    var likebtn_new=newPost.querySelector('.like-btn');
    if(likebtn_new){
        likebtn_new.style.backgroundColor = 'white';
        likebtn_new.setAttribute('data-liked', 'false');
    } 

    // 找到转发按钮，修改为删除按钮
    var shareBtn = newPost.querySelector('.share-btn');
    if (shareBtn) {
        // 修改按钮文本和图标
        shareBtn.textContent = '🗑️';
        // 为删除按钮设置ID
        var deleteBtnId = 'delete-btn-' + uniqueNumber;
        shareBtn.id = deleteBtnId;
        // 添加删除按钮的点击事件监听器
        shareBtn.addEventListener('click', DeleteButtonClick);
    }

    // 找到.main-content元素
    var mainContent = document.querySelector('.main-content');
    // 将新创建的post元素添加到.main-content中
    mainContent.insertBefore(newPost, mainContent.firstChild);
}

// 转发按钮
var shareBtn = document.querySelector('.share-btn');
if(shareBtn.id.startsWith('delete-btn-')){
    shareBtn.addEventListener('click', DeleteButtonClick);
}else{
    shareBtn.addEventListener('click', ShareButtonClick);
}


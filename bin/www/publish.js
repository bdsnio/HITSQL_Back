// 左侧按钮点击事件
document.getElementById('page3Btn').addEventListener('click', function() {
    window.location.href = 'myspace.html';
});

document.getElementById('homeBtn').addEventListener('click', function() {
    window.location.href = 'home.html'; // 确保这是主页的正确URL
});

// 发布按钮点击事件
document.getElementById('publishBtn').addEventListener('click', function() {
    var postContent = document.getElementById('postContent').value;
    if (postContent.trim() === '') {
        alert('发布内容不能为空！');
        return;
    }
    // 这里可以添加将发布内容提交到服务器的逻辑
    console.log('发布内容：' + postContent);
    alert('发布成功');
});
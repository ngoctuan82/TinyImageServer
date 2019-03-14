<uploadform>
		<input type='hidden' id='uploadurl' value='upload' >
			
			<form  draggable="true" action='' method='POST' id='myForm' enctype='multipart/form-data' target='hidden_iframe' onsubmit={startUpload}>

				<input id='uploadform_input' type='file' name='filestoupload[]' multiple=''>
				<br><br>
				<input id='uploadform_submit'  type='submit' value='Start Upload'>
				<br>
			</form>
			
			<!-- Progress bar -->
			<div id='progress_container'>
				<div id='progress'></div>
			</div>


			<!--
				hidden frame doing the upload process
				it's used to 'free' the browser window during upload phase
			--> 
			<iframe id='hidden_iframe' name='hidden_iframe' src='about:blank'></iframe>

		
  <!-- style -->
  <style scoped>
    h3 {
      font-size: 14px;
    }

	uploadform {
		border: 1px solid;
		display: block;
		padding: 10px;
		border-radius: 5px;
		height:300;
	}
	uploadform form
	{
		width:100%;
		height:100%;
	}
	uploadform form.dragover{
		 background-color: grey;
	}
	iframe{
		display:none;

	}
  </style>



  <!-- logic -->
  <script>
    var me = this
   	
    this.data = {
    	session:document.getElementById("session").value,
    	submittime:Date.now(),
    }
	// UI controls
	this.UI ={
		form:null,
		fileinput:null,
		submitinput:null
	};

    this.on('mount', function(){
		// on mount
		this.UI.form = $("form", this.root);
		this.UI.fileinput = $("#uploadform_input", this.root);
		this.UI.submitinput = $("#uploadform_submit", this.root);
		// init events for form drag & drop
		this.UI.form.off();
		this.UI.form.on("ondrop",this.OnDrop);
		this.UI.form.on("ondragover",this.OnDragOver);
		this.UI.form.on("ondragleave",this.OnLeave);
		
  	});
	this.on('upadte', function(){
		// on update
		this.UI.form = $("form", this.root);
		this.UI.fileinput = $("#uploadform_input", this.root);
		this.UI.submitinput = $("#uploadform_submit", this.root);
		// init events for form drag & drop
		this.UI.form.off();
		this.UI.form.on("ondrop",this.OnDrop);
		this.UI.form.on("ondragover",this.OnDragOver);
		this.UI.form.on("ondragleave",this.OnLeave);
	});

	/*
		starting to upload
	*/

    startUpload(e) {
      console.log("start upload");

      this.data.submittime = Date.now()
        
      var input = e.target[0]
      var form = input.parentElement
      
      form.action =`upload?uploadid=${ this.data.session + this.data.submittime}`;
      
 	  console.log(form.action); // debug

		setTimeout(this.progress(),200);

      return true;
      
    }
	/*
		call to server for progress of upload
	*/
    progress()
    {
    	 console.log("progress ");
    	var self = this;

    	var url =`progress?uploadid=${ this.data.session + this.data.submittime}`;
      
    	 fetch(url, {method:'get'})
    	.then(response => response.json())
		.then(jsonData => { 
			console.log(jsonData); 
			if(jsonData<100)
				setTimeout(self.progress(),200);
			else
			{
				this.UI.fileinput[0].value=null; // done upload
				alert("Upload Done");
			}
				
		})
		.catch(err => {

				console.error(err);
		});
    }

	/*Drag and Drop files support*/
	OnDrag(event)
	{	
		event.preventDefault();
		event.stopPropagation();

		this.UI.form.addClass('dragover');

	}
	OnLeave(event){
		event.preventDefault();
		event.stopPropagation();

		this.UI.form.removeClass('dragover');

	}
    OnDrop(event)
    {
    	event.preventDefault();
   		event.stopPropagation();
   		this.UI.form.removeClass('dragover');

		console.log(event);
    	
    	var droppedFiles = event.dataTransfer.files;

		var uploadinput = $("#uploadform_input", this.root)[0];
		if(uploadinput)
		{
			uploadinput.files = droppedFiles;
			this.UI.submitinput.trigger("click");
		}
		
    }
    // the mixin object bind
    this.mixin(OptsMixin);
  </script>

</uploadform>



<loginform>

 <!-- login area start -->
    <div class="login-area">
        <div class="container">
            <div class="login-box ptb--100">
                <form >
                    <div class="login-form-head">
                    	
                        <h4 class="titleLogin">Sign In</h4>
                        
                    </div>
                    <div class="login-form-body">
                        <div class="form-gp"> 
                            <input type="email" id="txtEmail" placeholder="Email address" value="user@simaget.com">
                            <i class="ti-email"></i>
                        </div>
                        <div class="form-gp">
                            <input type="password" id="txtPassword" placeholder="Password" value="1234">
                            <i class="ti-lock"></i>
                        </div>
                        
                        <div class="submit-btn-area">
                            <button id="btnSubmit" type="button" onclick = {OnClick}>Submit <i class="ti-arrow-right"></i></button>
                        </div>
                        <div class="form-footer text-center mt-5">
                            <p class="text-muted">Don't have an account? <a href="register.html">Sign up</a></p>
                        </div>
                    </div>
               <form>
            </div>
        </div>
    </div>
    <!-- login area end -->


	<script>
		
		this.UI={
			username:"",
			password:"",
			submit:null
		};
		
		InitUI()
		{
			this.UI.username = $("#txtEmail", this.root);
			this.UI.password = $("#txtPassword", this.root);
			this.UI.submit = $("#btnSubmit", this.root);

			this.UI.submit.off();
			this.UI.submit.on("click", this.OnClick);
		}
	  this.on('mount', function() {
	    // right after the tag is mounted on the page
	    console.log("mount");
	   
		this.InitUI();

	  })
	
	  this.on('update', function() {
	    // allows recalculation of context data before the update
	    console.log("update");

	    this.InitUI();
	  })
	
	  this.on('updated', function() {
	    // right after the tag template is updated after an update call
	    console.log("updated");
	  })
	  
	  OnClick()
	  {
	      console.log("click");
	      var username = this.UI.username.val();
	      var password = this.UI.password.val();
	      
	      var url =`api/user/login?EMAIL=${username}&PASSWORD=${password}`;
      
    	 fetch(url, {method:'get'})
    	.then(response => response.json())
		.then(jsonData => { 
			console.log(jsonData); 
			if(jsonData.IsError==false)
				window.location.replace(jsonData.Status);
			else
				alert(jsonData.Status);
		})
		.catch(err => {
				console.error(err);
		});
	      
	  }
	  
	    // the mixin object bind
    	this.mixin(OptsMixin);
	</script>
</loginform>

<preloader>
	<!-- preloader area start -->
    <div id="preloader">
        <div class="loader"></div>
    </div>
    <!-- preloader area end -->


    <script>
    this.on('mount', function() {
	    // right after the tag is mounted on the page
	    var preloader = $("#preloader", this.root);
	 	preloader.fadeOut(3000);

	 });
    </script>
</preloader>

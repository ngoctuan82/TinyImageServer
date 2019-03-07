<uploadform>
		<input type='hidden' id='uploadurl' value='upload' >
			
			<form  draggable="true" ondrop={OnDrop} ondragover={OnDrag} ondragleave={OnDragLeave}  action='' method='POST' id='myForm' enctype='multipart/form-data' target='hidden_iframe' onsubmit={startUpload}>

				<input id='uploadform_input' type='file' name='filestoupload[]' multiple=''>
				<br><br>
				<input type='submit' value='Start Upload'>
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
	
	this.UI ={
		form:null
	};

    this.on('mount', function(){
		// on mount
		this.UI.form = $("form", this.root);
  	});
	this.on('upadte', function(){
		// on update
		this.UI.form = $("form", this.root);
	});

	

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
		}
		
    }
  </script>

</uploadform>
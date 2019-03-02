<uploadform>

 	<input type='hidden' id='uploadurl' value='upload'>
			
		<!--
				progress handler URL -- javascript will use it to make periodic calls on server
				querying upload progress and showing it in progress bar
				You MUST insert in 'value' field the progress url (here 'progress')
			-->
			<input type='hidden' id='progressurl' value='progress'>
	
			<!--
				POST form
				action is a dummy value, will be filled by javascript code
				which sets the POST
			-->
			<form action='' method='POST' id='myForm' enctype='multipart/form-data' target='hidden_iframe' onsubmit={startUpload}>
			
				<!--
					ending [] in filestoupload[] makes a ValueArray of multipart data
					in Skylark arrays will be :
						filestoupload[]					a ValueArray with file contents
						filestoupload.content_type[]	a ValueArray with file content types
						filestoupload.filename[]		a ValueArray with filenames
					The 'multiple' field allows select and upload more files at once
				-->
				<input type='file' name='filestoupload[]' multiple=''>
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
  </style>



  <!-- logic -->
  <script>
    var me = this
    this.data = {
    	session:document.getElementById("session").value,
    	submittime:Date.now(),
    }
	

    startUpload(e) {
      console.log("start upload");

      this.data.submittime = Date.now()
        
      var input = e.target[0]
      var form = input.parentElement
      
      form.action +=`upload?uploadid=${ this.data.session + this.data.submittime}`;
      
 	 console.log(form.action);

      return true;
      
    }
  </script>

</uploadform>
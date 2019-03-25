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


<DiskUsagePieChart>

<div class="card">
	<div class="card-body" ref="container" >
		<h4 class="header-title">{data.Drive}</h4>
		<canvas ref="piechart" height="233" style="margin:auto"></canvas>
	</div>
</div>
	
<style>
	canvas{ margin:auto}
	diskusagepiechart{display:block}
</style>

     <script>
     //{ "Drive": "A:\\", "Total": "230.9 Gb", "Free": "59.4 Gb", "Usage": "171.5 Gb" }
     	this.data = 
				{ "Drive": "DEMO:\\", "Total": "230.9 Gb", "Free": "59.4 Gb", "Usage": "171.5 Gb" };

     	this.data = opts.data || this.data;
		//-----------------------------------------------
		InitUI()
		{	
			var container = this.refs.container;
			var ctx = this.refs.piechart;
			
			var labels =["Free:" + this.data.Free, "Usage:"+this.data.Usage];
			var values =[this.data.FreeVal, this.data.UsageVal];
			

				var chart = new Chart(ctx, {
				// The type of chart we want to create
				type: 'doughnut',
				// The data for our dataset
				data: {
					labels: labels,
					datasets: [{
						backgroundColor: [
							"#8919FE",
							"#12C498",
							"#F8CB3F"
						],
						borderColor: '#fff',
						data: values,
					}]
				},
				// Configuration options go here
				options: {
					legend: {
						display: true
					},
					animation: {
						easing: "easeInOutBack"
					},
					responsive: false,
					maintainAspectRatio:true
					
				}
			});
			chart.update();
		
			
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
	  
	 


     </script>

</DiskUsagePieChart>


<DiskUsagePieCharts>

	
		<DiskUsagePieChart   each={item, i in items}    data = {item} class={i>0?"mt-5":""}></DiskUsagePieChart>
		


	<script>
		var self = this;
		this.apikey = '123';  // should get from session
		this.API = `api/diskusage/${this.apikey}`;


		this.items = [];

		//-----------------------------------------
		this.on('mount', function() {
	    // right after the tag is mounted on the page
	    console.log("mount");
	   
    	 fetch(this.API, {method:'get'})
    	.then(response => response.json())
		.then(jsonData => { 
			console.log(jsonData); 
			if(jsonData.IsError==false)
			{
				self.items = jsonData.Data;
				self.update();
			}
			else
				console.error(jsonData.Status);
				
		})
		.catch(err => {

				console.error(err);
		});


	  });

	</script>

</DiskUsagePieCharts>



<AdminSummary>

	<div class="row">
                            
		<div class="col-md-6 mt-5 mb-3">
			<div class="card">
				<div class="seo-fact sbg1">
					<div class="p-4 d-flex justify-content-between align-items-center">
						<div class="seofct-icon"><i class="ti-thumb-up"></i>Backups</div>
						<h2>{item.Backups}</h2>
					</div>

				</div>
			</div>
		</div>
		<div class="col-md-6 mt-md-5 mb-3">
			<div class="card">
				<div class="seo-fact sbg2">
					<div class="p-4 d-flex justify-content-between align-items-center">
						<div class="seofct-icon"><i class="ti-share"></i>Downloads</div>
						<h2>{item.Downloads}</h2>
					</div>

				</div>
			</div>
		</div>
		<div class="col-md-6 mb-3 mb-lg-0">
			<div class="card">
				<div class="seo-fact sbg3">
					<div class="p-4 d-flex justify-content-between align-items-center">
						<div class="seofct-icon">Total Files</div>
						 <h2>{item.Files}</h2>
															  </div>
				</div>
			</div>
		</div>
		<div class="col-md-6">
			<div class="card">
				<div class="seo-fact sbg4">
					<div class="p-4 d-flex justify-content-between align-items-center">
						<div class="seofct-icon">Total Users</div>
						 <h2>{item.Users}</h2>

					</div>
				</div>
			</div>
		</div>
	</div>
			

	<script>
		var self = this;
		this.apikey = '123';  // should get from session
		this.API = `api/summary/${this.apikey}`;

		//{ "Status": "", "IsError": false, "Data": [ { "Backups": "0", "Downloads": "3", "Users": "3", "Files": "4" } ] }
		this.item = [];

		//-----------------------------------------
		this.on('mount', function() {
	    // right after the tag is mounted on the page
	    console.log("mount");
	   
    	 fetch(this.API, {method:'get'})
    	.then(response => response.json())
		.then(jsonData => { 
			console.log(jsonData); 
			if(jsonData.IsError==false)
			{
				self.item= jsonData.Data[0];
				self.update();
			}
			else
				console.error(jsonData.Status);
				
		})
		.catch(err => {

				console.error(err);
		});


	  });

	</script>

</AdminSummary>

<DownloadStatistic>

	<!-- Statistics area start -->
	
		<div class="card">
			<div class="card-body">
				<h4 class="header-title">Download Statistics</h4>
				<div id="user-statistics" ref ="downloadstatistic"></div>
			</div>
		</div>
	
	<!-- Statistics area end -->

<script>
		var self = this;
		this.apikey = '123';  // should get from session
		this.API = `api/download/${this.apikey}`;

		//[{"ID":-1,"USERID":null,"LOGDATE":737503,"NOOFUPLOADFILE":0,"NOOFDOWNLOADFILE":1,"TOTALUPLOADSIZE":0,"TOTALDOWNLOADSIZE":1234567},{"ID":-1,"USERID":null,"LOGDATE":737504,"NOOFUPLOADFILE":0,"NOOFDOWNLOADFILE":4,"TOTALUPLOADSIZE":0,"TOTALDOWNLOADSIZE":4938268}]
		this.items=null;

		this.UI={
			chart:null
		};

		InitUI(items)
		{
			   var downloadstatistic = this.refs.downloadstatistic;

			   this.UI.chart = AmCharts.makeChart(downloadstatistic, {
				"type": "serial",
				"theme": "light",
				"marginRight": 0,
				"marginLeft": 40,
				"autoMarginOffset": 20,
				"dataDateFormat": "MM-DD-YYYY",
				"valueAxes": [{
					"id": "v1",
					"axisAlpha": 0,
					"position": "left",
					"ignoreAxisWidth": true
				}],
				"balloon": {
					"borderThickness": 1,
					"shadowAlpha": 0
				},
				"graphs": [{
					"id": "g1",
					"balloon": {
						"drop": true,
						"adjustBorderColor": false,
						"color": "#ffffff",
						"type": "smoothedLine"
					},
					"fillAlphas": 0.2,
					"bullet": "round",
					"bulletBorderAlpha": 1,
					"bulletColor": "#FFFFFF",
					"bulletSize": 5,
					"hideBulletsCount": 50,
					"lineThickness": 2,
					"title": "red line",
					"useLineColorForBulletBorder": true,
					"valueField": "value",
					"balloonText": "<span style='font-size:18px;'>[[value]]</span>"
				}],
				"chartCursor": {
					"valueLineEnabled": true,
					"valueLineBalloonEnabled": true,
					"cursorAlpha": 0,
					"zoomable": false,
					"valueZoomable": true,
					"valueLineAlpha": 0.5
				},
				"valueScrollbar": {
					"autoGridCount": true,
					"color": "#5E72F3",
					"scrollbarHeight": 30
				},
				"categoryField": "date",
				"categoryAxis": {
					"parseDates": true,
					"dashLength": 1,
					"minorGridEnabled": true
				},
				"export": {
					"enabled": false
				},
				"dataProvider": items

				
		});
		}
		//-----------------------------------------
		this.on('mount', function() {
			// right after the tag is mounted on the page
			console.log("mount");

			 fetch(this.API, {method:'get'})
			.then(response => response.json())
			.then(jsonData => { 
				console.log(jsonData); 
				if(jsonData.IsError==false)
				{
					self.items= jsonData.Data.map(obj => ( {"date":obj.LOGDATE, "value":obj.NOOFDOWNLOADFILE} ));
					self.InitUI(self.items);
					self.update();
				}
				else
					console.error(jsonData.Status);

			})
			.catch(err => {

					console.error(err);
			});


	 	 });

	 	 
	  this.on('update', function() {
	    // allows recalculation of context data before the update
	    console.log("update");

	    //self.InitUI(self.items);
	  })

	</script>
</DownloadStatistic>



<adminform>

	
<div class="card">
	<div class="card-body">
		<h4 class="header-title">Admin</h4>

	   <div class="row">
	   		<div class="col-12 form-gp">
				<input type="email" ref="EMAIL" placeholder="Email" value={item.EMAIL} onchange={OnChange}>
				<i class="ti-email"></i>
			</div>
			<div class="col-12 form-gp">
				<input type="password" ref="PASSWORD" placeholder="Password"  value={item.PASSWORD}  onchange={OnChange}>
				<i class="ti-shield"></i>
			</div>
			<div class="col-12 form-gp">
				<input type="text" ref="FULLNAME" placeholder="Full Name" value={item.FULLNAME}  onchange={OnChange} >
				<i class="ti-user"></i>
			</div>
			<div class="col-12 form-gp">	
				<input type="phone" ref="PHONE" placeholder="Phone"  value={item.PHONE}  onchange={OnChange}>
				<i class="ti-mobile"></i>
			</div>
		</div>

		<div class="row">
			
			<div class="col-4">
				<button onclick={OnSaveClick} type="button" ref="btnSave" class="btn btn-primary mt-4 pr-4 pl-4">Save</button>
			</div>

		</div>


	</div>
</div>

		


	<script>
		var self = this;
		this.APIKEY = '123';  // should get from session
		this.API={
			GET:`api/user/get/${this.APIKEY}`,
			UPDATE:`api/user/update/${this.APIKEY}`
		};
		//--------

		this.item={
			EMAIL:"",
			PASSWORD:"",
			FULLNAME:"",
			PHONE:"",
		};
		
		InitUI()
		{
			

		}

		this.on('mount', function() {
			console.log("mount");
			this.LoadData();
			
		})

		 this.on('update', function() {
			console.log("update");
	  	})

	  	LoadData()
	  	{
	  		console.log("Load Data");
	  		 fetch(this.API.GET, 
	  		 {
	  		 	method:'get'
	  		 })
			.then(response => response.json())
			.then(jsonData => {
				console.log(jsonData);
				if(jsonData.IsError==false)
				{
					self.item = jsonData.Data[0] || self.item;
					
					self.update();
				}
				else
					console.error(jsonData.Status);

			})
			.catch(err => {

					console.error(err);
			});
	  	}

		OnChange(e)
		{
			var ctrl= e.target;
			this.item[ctrl.attributes.ref.value] = ctrl.value;
		}

	  	OnSaveClick(e)
	  	{
	  		console.log("On click");

			var url = `${this.API.UPDATE}?${QueryStr(this.item)}`;
			console.log(url);
			
	  		fetch(url, {method:'get'})
			.then(response => response.json())
			.then(jsonData => { 
				console.log(jsonData); 
				if(jsonData.IsError==false)
				{
					console.log("DONE updated");
				}
				else
					console.error(jsonData.Status);

			})
			.catch(err => {

					console.error(err);
			});

	  	}


	</script>

</adminform>



<serverform>

	
<div class="card">
	<div class="card-body">
		<h4 class="header-title">Server Info</h4>

	   <div class="row">
	   		<div class="col-12 form-gp">
	   			<label>Root Path</label>
				<input type="text" ref="ROOTPATH" value={item.ROOTPATH} onchange={OnChange}>
				<i class="ti-email"></i>
			</div>
			<div class="col-12 form-gp">
				<label>Static Path</label>
				<input type="text" ref="STATICPATH"  value={item.STATICPATH}  onchange={OnChange}>
				<i class="ti-shield"></i>
			</div>
			<div class="col-12 form-gp">
				<label>Image Path</label>
				<input type="text" ref="IMAGEPATH" value={item.IMAGEPATH}  onchange={OnChange} >
				<i class="ti-user"></i>
			</div>
			<div class="col-12 form-gp">	
				<label>Backup Path</label>
				<input type="text" ref="BACKUPPATH"   value={item.BACKUPPATH}  onchange={OnChange}>
				<i class="ti-mobile"></i>
			</div>
		</div>


	</div>
</div>

		<style>
serverform label{
	position: inherit !important;
	color: none !important
}






	color:none  !important

}
		</style>


	<script>
		var self = this;
		this.APIKEY = '123';  // should get from session
		this.API={
			GET:`api/adminsetting/get/${this.APIKEY}`,
		//	UPDATE:`api/adminsetting/update/${this.APIKEY}`
		};
		//--------

		this.item={
			ROOTPATH:"",
			STATICPATH:"",
			IMAGEPATH:"",
			BACKUPPATH:"",
		};
		
		InitUI()
		{
			

		}

		this.on('mount', function() {
			console.log("mount");
			this.LoadData();
			
		})

		 this.on('update', function() {
			console.log("update");
	  	})

	  	LoadData()
	  	{
	  		console.log("Load Data");
	  		 fetch(this.API.GET, 
	  		 {
	  		 	method:'get'
	  		 })
			.then(response => response.json())
			.then(jsonData => {
				console.log(jsonData);
				if(jsonData.IsError==false)
				{
					self.item = jsonData.Data[0] || self.item;
					
					self.update();
				}
				else
					console.error(jsonData.Status);

			})
			.catch(err => {

					console.error(err);
			});
	  	}

		OnChange(e)
		{
			var ctrl= e.target;
			this.item[ctrl.attributes.ref.value] = ctrl.value;
		}

	  	

	</script>

</serverform>

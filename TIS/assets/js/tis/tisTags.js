<imageblock>

    <div class="card card-bordered">
        <img class="card-img-top img-fluid" src="{data.SHARELINK}" alt="image">
        <div class="card-body">
            <h5 class="title">{data.TAG}</h5>
            
            <div class="btn-group mb-xl-3" role="group" aria-label="Basic example">
				<button onclick={OnClickShare} type="button" class="btn btn-xs btn-outline-primary"><i class="ti-share"/>Share</button>
	 <!--		<button onclick={OnClickDetail} type="button" class="btn btn-xs btn-outline-primary"><i class="ti-new-window"/>Edit</button>
	 -->	
				<button onclick={OnClickDeactive} type="button" class="btn btn-xs {item.STATUS?'btn-primary':'btn-outline-primary'}"><i class="ti-unlink"/>{item.STATUS?"Deactive":"Active"}</button>
			</div>
        
           
        </div>
    </div>
	


     <script>
   
   		var self = this;
		this.APIKEY = this.opts.LOGAPIKEY;  // should get from session
		this.API = {
			SEARCH:`api/imagefile/get/${this.APIKEY}`,
			UPDATE:`api/imagefile/update/${this.APIKEY}`,
		};
		
     	this.item = this.opts.riotSrc;
        this.data ={
        	SHARELINK:this.item.SHARELINK,
        	TAG:this.item.TAG
        };
		//-----------------------------------------------
		InitUI()
		{	
		
		}

        this.on('mount', function() {
            // right after the tag is mounted on the page
            console.log("mount");
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
        //--------------------------
        OnClickShare()
	  	{
            console.log("OnClickShare");
			var uri=`${window.location.hostname}:${window.location.port}/${this.data.SHARELINK}`;
            window.prompt("Share link of the image", uri);
        }
        
         OnClickDetail()
	  	{
            console.log("OnClickDetail");
        }
         OnClickDeactive()
	  	{
            console.log("OnClickDeactive");
            var item =this.item;

			item.STATUS=item.STATUS?0:1;
			var obj={ID:item.ID, STATUS: item.STATUS};
			

			this.DoUpdate(obj);
        }
     

		DoUpdate(item)
		{
			var url = `${this.API.UPDATE}?${QueryStr(item)}`;
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

</imageblock>





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
                            <p class="text-muted">Don't have an account? <a href="signup">Sign up</a></p>
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
			{
				localStorage.setItem("ADMINID", jsonData.Data[0].ID);
				localStorage.setItem("SelectedUser", jsonData.Data[0].ID);
				window.location.replace(jsonData.Status);
			}
				
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



<signupform>

 <!-- login area start -->
    <div class="login-area">
        <div class="container">
            <div class="login-box ptb--100">
                <form >
                    <div class="login-form-head">
                    	
                        <h4 class="titleLogin">Sign In</h4>
                        
                    </div>
                    <div class="login-form-body">
                        
                        
                        <div class="form-group">
							<i class="ti-user"></i> 
                            <input class="form-control mt-2"  type="text" ref="FULLNAME" placeholder="Full Name" value={item.FULLNAME}  onchange={OnChange} >				
                        </div>
                        <div class="form-group">
                            <i class="ti-email"></i>
							<input class="form-control mt-2"  type="email" ref="EMAIL" placeholder="Email" value={item.EMAIL} onchange={OnChange}>
                        </div>
                        <div class="form-group">
                            <i class="ti-calendar"></i>
							<input class="form-control mt-2" ref="DATEOFBIRTH" type="date" value="2019-03-05" value={item.EMAIL} onchange={OnChange} >
                        </div>
                        <div class="form-group">
                            	<i class="ti-mobile"></i>
								<input class="form-control mt-2"  type="phone" ref="PHONE" placeholder="Phone"  value={item.PHONE}  onchange={OnChange}>
                        </div>
                        <div class="form-group">
                           <i class="ti-shield"></i>
							<input class="form-control mt-2"  type="password" ref="PASSWORD" placeholder="Password"  value={item.PASSWORD}  onchange={OnChange}>
                        </div>
                        <div class="form-group">
                           <i class="ti-shield"></i>
							<input class="form-control mt-2" type="password" ref="CONFIRMPASSWORD" placeholder="Password"    onchange={OnChange}>
                        </div>
                        
                      
                        
                        <div class="submit-btn-area">
                             <div class="login-other row mt-4">
                                <div class="col-6">
                                	<button ref="btnClose" type="button" onclick = {OnClickClose}>Cancel<i class="ti-close"></i></button>
                                </div>
                                <div class="col-6">	
                                    <button ref="btnSubmit" type="button" onclick = {OnClick}>Sign Up<i class="ti-arrow-right"></i></button>
                                </div>
                            </div>
                        </div>
                       
                    </div>
               <form>
            </div>
        </div>
    </div>
    <!-- login area end -->


	<script>
		var self = this;
		//this.APIKEY = this.opts.LOGAPIKEY;  // should get from session
		this.API={
			CREATE:`api/user/create`
		};
		//--------
        
        this.item={
			EMAIL:"",
			FULLNAME:"",
			DATEOFBIRTH:"",
			PHONE:"",
			PASSWORD:"",
            CONFIRMPASSWORD:"",
		};      
      
	  this.on('mount', function() {
	    // right after the tag is mounted on the page
	    console.log("mount");
	   
	  })
	
	  this.on('update', function() {
	    // allows recalculation of context data before the update
	    console.log("update");

	 
	  })
	
	  this.on('updated', function() {
	    // right after the tag template is updated after an update call
	    console.log("updated");
	  });

      OnChange(e)
		{
			var ctrl= e.target;
			this.item[ctrl.attributes.ref.value] = ctrl.value;
		}
      
      
	  OnClickClose()
	  {
	  	window.location.href="login";
	  }
	  
	  OnClick()
	  {
	      console.log("click");

			if(this.refs.PASSWORD.value !== this.refs.CONFIRMPASSWORD.value)
			{
				alert("Password does not match");
				return;
			}
//-----------------------------
	     var url = `${this.API.CREATE}?${QueryStr(this.item)}`;
      
    	 fetch(url, {method:'get'})
    	.then(response => response.json())
		.then(jsonData => { 
			console.log(jsonData); 
			if(jsonData.IsError==false)
			{
				console.log("DONE Create");
				window.location.replace("login");
			}
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
</signupform>


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
					responsive: true,
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
		this.APIKEY = this.opts.LOGAPIKEY;  // should get from session
		this.API = `api/diskusage/${this.APIKEY}`;


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
		this.APIKEY = this.opts.LOGAPIKEY;  // should get from session
		this.API = `api/summary/${this.APIKEY}`;

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
		this.APIKEY = this.opts.LOGAPIKEY;  // should get from session
		this.API = `api/download/${this.APIKEY}`;

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



<UserDownloadStatistic>

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
		this.APIKEY = this.opts.LOGAPIKEY;  // should get from session
		this.API = `api/download/${this.APIKEY}`;

		//[{"ID":-1,"USERID":null,"LOGDATE":737503,"NOOFUPLOADFILE":0,"NOOFDOWNLOADFILE":1,"TOTALUPLOADSIZE":0,"TOTALDOWNLOADSIZE":1234567},{"ID":-1,"USERID":null,"LOGDATE":737504,"NOOFUPLOADFILE":0,"NOOFDOWNLOADFILE":4,"TOTALUPLOADSIZE":0,"TOTALDOWNLOADSIZE":4938268}]
		this.items=null;

		this.SEARCH={USERID:null};

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
			
			this.SEARCH.USERID = localStorage.getItem("SelectedUser");
			 
			this.LoadData(this.SEARCH);
	 	 });

	 	 LoadData(params)
	 	 {
	 	 	var url = `${this.API}?${QueryStr(params)}`;
	 	 	fetch(url, {method:'get'})
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
	 	 }

	 	 
	  this.on('update', function() {
	    // allows recalculation of context data before the update
	    console.log("update");

	    //self.InitUI(self.items);
	  })

	</script>
</UserDownloadStatistic>


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
		this.APIKEY = this.opts.LOGAPIKEY;  // should get from session
		this.API={
			GET:`api/user/get/${this.APIKEY}`,
			UPDATE:`api/user/update/${this.APIKEY}`
		};
		//--------
		this.SEARCH={
			APIKEY: this.opts.ADMINID,
			ISADMIN:1
		};

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
	  		var url=`${this.API.GET}?${QueryStr(this.SEARCH)}`;
	  		 fetch(url, 
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
		<h4 class="header-title">Configuration</h4>

	   <div class="row">
	   		<div class="col-12 form-gp">
	   			<label>Root Path</label>
				<input readonly type="text" ref="ROOTPATH" value={item.ROOTPATH} onchange={OnChange}>
				<i class="ti-home"></i>
			</div>
			<div class="col-12 form-gp">
				<label>Static Path</label>
				<input readonly type="text" ref="STATICPATH"  value={item.STATICPATH}  onchange={OnChange}>
				<i class="ti-folder"></i>
			</div>
			<div class="col-12 form-gp">
				<label>Image Path</label>
				<input readonly type="text" ref="IMAGEPATH" value={item.IMAGEPATH}  onchange={OnChange} >
				<i class="ti-image"></i>
			</div>
			<div class="col-12 form-gp">	
				<label>Backup Path</label>
				<input readonly type="text" ref="BACKUPPATH"   value={item.BACKUPPATH}  onchange={OnChange}>
				<i class="ti-server"></i>
			</div>
		</div>


	</div>
</div>

		<style>
			serverform label{
				position: inherit !important;
				color: none !important
			}
		</style>


	<script>
		var self = this;
		this.APIKEY = this.opts.LOGAPIKEY;  // should get from session
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


<backupform>

 <!-- Backup form start -->
                  <div class="card">
                            <div class="card-body">
                                
                                <div class="header-title">
                                    
                                         <h4>
                                            Full Backup & Restore
                                         </h4>
                                          <div class="row">
                                            <div class="col-4">
                                                <button onclick={OnClickBackup} type="button" class="btn btn-warning mt-4 pr-4 pl-4">Backup Now</button>
                                            </div>
                                           
                                          
                                        </div>
                                   
                                </div>

                                

                                <div class="single-table mt-3">
                                    <div class="table-responsive">
                                        <table class="table text-center">
                                            <thead class="text-uppercase bg-primary">
                                                <tr class="text-white">
                                                    <th scope="col">Date</th>
                                                    <th scope="col">PATH</th>
                                                    <th scope="col">Type</th>
                                                    <th scope="col">Status</th>                                              
                                                    <th scope="col">Action</th>
                                                </tr>
                                            </thead>
                                            <tbody>

                                                <tr each={item in items}>
                                                    
                                                    <td>{item.CREATEDDATE}</td>
                                                    <td>{item.FOLDERPATH}</td>
                                                    <td>{item.ISBACKUPTASK?"Backup":"Restore"}</td>
                                                    <td><span class="status-p bg-primary">{item.STATUS==0?"Proccessing":"Ready"}</span></td>
                                                    <td  > <i   onclick={OnClickRestore} if={item.STATUS==1 && item.ISBACKUPTASK==true}  class="ti-back-right"></i>  </td>
                         
                                                </tr>
                                                
                                            </tbody>
                                        </table>
                                    </div>
                                </div>
                            </div>
                        </div>
                  <!-- Backup form end -->



<script>
	var self = this;
		this.APIKEY = this.opts.LOGAPIKEY;  // should get from session
		this.API={
			GET:`api/backuprestoretask/get/${this.APIKEY}`,
			CREATE:`api/backuprestoretask/create/${this.APIKEY}`,
			BACKUP:`backup`,

		};

		this.items =[];

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
					self.items = jsonData.Data || self.items;
					
					self.update();

					//self.DoBackup(jsonData.Data[0].ID);
				}
				else
					console.error(jsonData.Status);

			})
			.catch(err => {

					console.error(err);
			});
	  	}

		OnClickBackup()
		{
			console.log("click backup");
			var params = {ISBACKUPTASK:1};
			this.DoCreate(params);
			
		}

		OnClickRestore(e, item)
		{
			console.log("Click Restore");
			var item = e.item.item;
			
			var params = {
					FROMID: item.ID,
					ISBACKUPTASK:0
			};
			this.DoCreate(params);
		}

		DoCreate(params)
		{
			 
			 var url = `${this.API.CREATE}?${QueryStr(params)}`;

			 fetch(url, 
	  		 {
	  		 	method:'get'
	  		 })
			.then(response => response.json())
			.then(jsonData => {
				console.log(jsonData);
				if(jsonData.IsError==false)
				{
					
					if(jsonData.Data.length>0)
					{
						self.items.unshift(jsonData.Data[0]);
						self.update();

						self.DoBackup(jsonData.Data[0].ID);
					}
				}
				else
					console.error(jsonData.Status);

			})
			.catch(err => {

					console.error(err);
			});

		}


			DoBackup(backupid)
			{
				var param={APIKEY:this.APIKEY, BACKUPID:backupid};
				 var url = `${this.API.BACKUP}?${QueryStr(param)}`;

				 fetch(url, 
				 {
					method:'get'
				 })
				.then(response => response.json())
				.then(jsonData => {
					console.log(jsonData);
					if(jsonData==true)
					{
						self.LoadData();
					}
					else
						console.error("Can not backup/restore");

				})
				.catch(err => {

						console.error(err);
				});
			}
	
</script>
</backupform>


<UsersPieChart>

<div class="card">
	<div class="card-body" ref="container" >
		<h4 class="header-title">Total Users</h4>
		<canvas ref="piechart" height="233" style="margin:auto"></canvas>
	</div>
</div>
	
<style>
	canvas{ margin:auto}
	diskusagepiechart{display:block}
</style>

     <script>
   
   		var self = this;
		this.APIKEY = this.opts.LOGAPIKEY;  // should get from session
		this.API = `api/userstotal/${this.APIKEY}`;
		
     	this.data = {Active: 60, Deleted: 1};
		//-----------------------------------------------
		InitUI()
		{	
			var container = this.refs.container;
			var ctx = this.refs.piechart;
			
			var labels =[ "Deleted:","Active:"];
			var values =this.data;
			

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
					responsive: true,
					maintainAspectRatio:true

				}
			});
			chart.update();
			
		}

	 
	  this.on('update', function() {
	    // allows recalculation of context data before the update
	    console.log("update");

	    this.InitUI();
	  })
	
	  this.on('updated', function() {
	    // right after the tag template is updated after an update call
	    console.log("updated");
	  })
	  	

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
				self.data = jsonData.Data.map(e=> e.USERS);
				
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

</UsersPieChart>


<usermanagement>


<!-- user management form start -->
                  <div class="card">
                            <div class="card-body">
                                
                                <div class="header-title">               
                                        <!-- search row start -->
										<div class="row">
											<div class="col-12">
												<div class="search-box pull-left">
													<form action="#">
														<input ref="txtSearch" type="text" name="search" placeholder="Search by name..." required>
														<i onclick={OnClickSearch} class="ti-search"></i>
													</form>
												</div>
											</div>
										</div>
										<!-- search row end -->
                                   
                                </div>

                                

                                <div class="single-table mt-3">
                                    <div class="table-responsive">
                                        <table class="table table-hover progress-table text-center">
                                            <thead class="text-uppercase bg-primary">
                                                <tr class="text-white">
                                                	<th scope="col">ID<i  onclick={OnClickOrderID}  class="ti-exchange-vertical ml-2"></i></th>
                                                    <th scope="col">Name <i  onclick={OnClickOrderName}  class="ti-exchange-vertical  ml-2"></i></th>
                                                    <th scope="col">DOB <i  onclick={OnClickOrderDOB}  class="ti-exchange-vertical ml-2"></i></th>
                                                    <th scope="col">Email<i  onclick={OnClickOrderEmail}  class="ti-exchange-vertical ml-2"></i></th>
                                                    <th scope="col">Status<i  onclick={OnClickOrderStatus}  class="ti-exchange-vertical ml-2"></i></th>
                                                    <th scope="col">Action</th>
                                                </tr>
                                            </thead>
                                            <tbody>
                                                <tr each={item, i in items}>
                                                    <td   onclick={OnClickRowItem} >{item.ID}</td>
                                                    <td   onclick={OnClickRowItem} >{item.FULLNAME}</td>
                                                    <td   onclick={OnClickRowItem} >{item.DATEOFBIRTH}</td>
                                                    <td   onclick={OnClickRowItem} >{item.EMAIL}</td>
                                                    <td   onclick={OnClickRowItem} > <span class="status-p {item.STATUS?'bg-warning':'bg-primary'}">{item.STATUS?"Active":"Deleted"}</span>  </td>
                                                    <td  onclick={parent.OnClickDeleteRestore} > <i  class="{item.STATUS?'ti-trash':'ti-back-right'}"></i>  </td>
                                                  
                                                </tr>
                                                
                                            </tbody>
                                        </table>
                                        <!-- Pagination start -->
										 <nav aria-label="Page navigation example">
											<ul class="pagination">
												<li class="page-item">
													<a onclick={OnClickPrevPage} class="page-link" href="#" aria-label="Previous">
														<span aria-hidden="true">&laquo;</span>
														<span class="sr-only">Previous</span>
													</a>
												</li>

												<li  each={page in pages}  class="page-item {this.SEARCH.PAGE==page-1?'disabled':''}">
													<a href="#" class="page-link" onclick={OnClickPage}>{page}</a>
												</li>



												<li class="page-item">
													<a onclick={OnClickNextPage} class="page-link" href="#" aria-label="Next">
														<span aria-hidden="true">&raquo;</span>
														<span class="sr-only">Next</span>
													</a>
												</li>
											</ul>
										</nav>
											
										
										<!-- Pagination end -->
                                    </div>
                                </div>
                            </div>
                        </div>
<!-- user management form end -->
<script>
	var self = this;
		this.APIKEY = this.opts.LOGAPIKEY;  // should get from session
		this.API={
			SEARCH:`api/user/get/${this.APIKEY}`,
			UPDATE:`api/user/update/${this.APIKEY}`,
			TOTALUSERS:`api/userstotal/${this.APIKEY}`
		};

		this.SEARCH={
			PAGE:0,
			SIZE:10,
			FULLNAME:"",
			ORDERBY:"",
			DESC:0
		};
		
		this.pages =[];
		this.items =[];

		this.on('mount', function() {
			console.log("mount");
			
			this.LoadTotalUsers(this.LoadData);
		})

		 this.on('update', function() {
			console.log("update");
	  	})
		
		LoadTotalUsers(fn)
		{
			fetch(this.API.TOTALUSERS, 
	  		 {
	  		 	method:'get'
	  		 })
			.then(response => response.json())
			.then(jsonData => {
				console.log(jsonData);
				if(jsonData.IsError==false)
				{
					var data = jsonData.Data;
					var totals = 0;
					data.forEach((a)=>totals+=a.USERS);
					var pages =Math.ceil( totals/(this.SEARCH.SIZE?this.SEARCH.SIZE:20) );
					// generation 
					self.pages = [];
					for(i=0;i<pages;i++) self.pages.push(i+1);
				}
				else
					console.error(jsonData.Status);

			})
			.then(r=>
			{
				if(fn) fn();// callback
			})
			.catch(err => {

					console.error(err);
			});
		}
		
	  	LoadData()
	  	{
	  		console.log("Load Data");
	  		var url = `${this.API.SEARCH}?${QueryStr(this.SEARCH)}`;

	  		 fetch(url, 
	  		 {
	  		 	method:'get'
	  		 })
			.then(response => response.json())
			.then(jsonData => {
				console.log(jsonData);
				if(jsonData.IsError==false)
				{
					self.items = jsonData.Data || self.items;
					
					self.update();
				}
				else
					console.error(jsonData.Status);

			})
			.catch(err => {

					console.error(err);
			});
	  	}

		
		OnClickDeleteRestore(event)
		{
			console.log("Click Delete Restore");
			console.log(event.item);
			var item = event.item.item;
			var index = event.item.i;
			item.STATUS=item.STATUS?0:1;
			var obj={ID:item.ID, STATUS: item.STATUS};
			
			
			this.DoUpdate(obj, index);
		}

		DoUpdate(params, index)
		{
			 
			 var url = `${this.API.UPDATE}?${QueryStr(params)}`;

			 fetch(url, 
	  		 {
	  		 	method:'get'
	  		 })
			.then(response => response.json())
			.then(jsonData => {
				console.log(jsonData);
				if(jsonData.IsError==false)
				{
					
					if(jsonData.Data.length>0)
					{
						self.items[index] = jsonData.Data[0];
						self.update();
					}
				}
				else
					console.error(jsonData.Status);

			})
			.catch(err => {

					console.error(err);
			});
		}

		OnClickOrderID()
		{
			this.SEARCH.ORDERBY = "ID";
			this.SEARCH.DESC=this.SEARCH.DESC?0:1;
			this.LoadData();
		}
		OnClickOrderName()
		{
			this.SEARCH.ORDERBY = "FULLNAME";
			this.SEARCH.DESC=this.SEARCH.DESC?0:1;
			this.LoadData();
		}
		OnClickOrderDOB()
		{
			this.SEARCH.ORDERBY = "DATEOFBIRTH";
			this.SEARCH.DESC=this.SEARCH.DESC?0:1;
			this.LoadData();
		}
		OnClickOrderEmail()
		{
			this.SEARCH.ORDERBY = "EMAIL";
			this.SEARCH.DESC=this.SEARCH.DESC?0:1;
			this.LoadData();
		}
		OnClickOrderStatus()
		{
			this.SEARCH.ORDERBY = "STATUS";
			this.SEARCH.DESC=this.SEARCH.DESC?0:1;
			this.LoadData();
		}
		

		OnClickSearch()
		{
			var txtSearch = this.refs.txtSearch;
			this.SEARCH.FULLNAME= txtSearch.value;

			this.LoadData();
		}

		
		//--------- pagination
		OnClickPage(event)
		{
			event.preventDefault();

			var item = event.item;
			this.SEARCH.PAGE = item.page-1;
			this.LoadData();
		}

		OnClickRowItem(event)
		{
			localStorage.setItem("SelectedUser", event.item.item.ID );
			window.location.href = "adminuserdetail";
		}
	
</script>
</usermanagement>



<FilesPieChart>

<div class="card">
	<div class="card-body" ref="container" >
		<h4 class="header-title">Total files</h4>
		<canvas ref="piechart" height="233" style="margin:auto"></canvas>
	</div>
</div>
	
<style>
	canvas{ margin:auto}
	diskusagepiechart{display:block}
</style>

     <script>
   
   		var self = this;
		this.APIKEY = this.opts.LOGAPIKEY;  // should get from session
		this.API = `api/filestotal/${this.APIKEY}`;
		
		this.SEARCH={USERID:0};

     	this.data = {labels: [], data: []};
		//-----------------------------------------------
		InitUI()
		{	
			var container = this.refs.container;
			var ctx = this.refs.piechart;
			
			var labels =this.data.labels;
			var values =this.data.data;
			

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
					responsive: true,
					maintainAspectRatio:true

				}
			});
			chart.update();
			
		}

	  	this.on('mount', function() {
	    // right after the tag is mounted on the page
	    console.log("mount");
	   
		this.SEARCH.USERID = localStorage.getItem("SelectedUser");
		this.LoadData();

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

	  LoadData()
	  {
	  	var url =`${this.API}?${QueryStr(this.SEARCH)}`;
    	 fetch(url, {method:'get'})
    	.then(response => response.json())
		.then(jsonData => { 
			console.log(jsonData); 
			if(jsonData.IsError==false)
			{
				jsonData.Data.map(e=> { 
								self.data.labels.push(e.STATUS?"Active":"Deleted"); 
								self.data.data.push(e.FILES) });
				
				self.update();
			}
			else
				console.error(jsonData.Status);
				
		})
		.catch(err => {

				console.error(err);
		});
	  }
	  	

	
	 


     </script>

</FilesPieChart>

<Userform>	
<div class="card">
	<div class="card-body">
		<h4 class="header-title">User Info</h4>

	   <div class="row">
	   		<div class="col-12 form-gp">
				<input type="text" ref="FULLNAME" placeholder="Full Name" value={item.FULLNAME}  onchange={OnChange} >
				<i class="ti-user"></i>
			</div>
	   		<div class="col-12 form-gp">
				<input type="email" ref="EMAIL" placeholder="Email" value={item.EMAIL} onchange={OnChange}>
				<i class="ti-email"></i>
			</div>
			<div class="col-12 form-gp">	
				<input type="phone" ref="PHONE" placeholder="Phone"  value={item.PHONE}  onchange={OnChange}>
				<i class="ti-mobile"></i>
			</div>
			<div class="col-12 form-gp">
				<input readonly type="text" ref="APIKEY" placeholder="Apikey"  value={item.APIKEY}  onchange={OnChange}>
				<i class="ti-shield"></i>
			</div>
			<div class="col-12 form-gp">
				<input type="password" ref="PASSWORD" placeholder="Password"  value={item.PASSWORD}  onchange={OnChange}>
				<i class="ti-shield"></i>
			</div>
			<div class="col-12 form-gp">
				<input type="password" ref="CONFIRMPASSWORD" placeholder="Password"  value={item.PASSWORD}  onchange={OnChange}>
				<i class="ti-shield"></i>
			</div>
			
		</div>

		<div class="row">
			
			<div class="col-12">
				<button onclick={OnSaveClick} type="button" ref="btnSave" class="btn btn-primary mt-4 pr-4 pl-4">Save</button>
				<button if={item.ISADMIN==0} onclick={OnDeleteActiveClick} type="button" ref="btnDeleteActive" class="btn btn-danger mt-4 ml-2 pr-4 pl-4">{item.STATUS?"Delete":"Active"}</button>
			</div>
		

		</div>


	</div>
</div>

		


	<script>
		var self = this;
		this.APIKEY = this.opts.LOGAPIKEY;  // should get from session
		this.API={
			GET:`api/user/get/${this.APIKEY}`,
			UPDATE:`api/user/update/${this.APIKEY}`
		};
		//--------
		this.TARGET= {ID:null}; // selected user
		
		this.item={
			ID:null,
			EMAIL:"",
			//APIKEY:"",
			FULLNAME:"",
			DATEOFBIRTH:"",
			STATUS:"",
			PHONE:"",
			//PASSWORD:"",
			ISADMIN:0
		};
		
		InitUI()
		{
			

		}

		this.on('mount', function() {
			console.log("mount");
			this.TARGET.ID = localStorage.getItem("SelectedUser");
			

			this.LoadData();
			
		})

		 this.on('update', function() {
			console.log("update");
	  	})

	  	LoadData()
	  	{
	  		console.log("Load Data");
	  		var url =`${this.API.GET}?${QueryStr(this.TARGET)}`;
	  		 fetch(url, 
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

//confirm password
			if(this.refs.PASSWORD.value !== this.refs.CONFIRMPASSWORD.value)
			{
				alert("Password does not match");
				return;
			}
//
			this.item.CONFIRMPASSWORD = this.refs.CONFIRMPASSWORD.value;
			this.DoUpdate(this.item);
	  	}

		OnDeleteActiveClick(event)
		{
			console.log("Click Delete Restore");
			
			var item =this.item;

			item.STATUS=item.STATUS?0:1;
			var obj={ID:item.ID, STATUS: item.STATUS};
			

			this.DoUpdate(obj);
		}

		DoUpdate(item)
		{
			var url = `${this.API.UPDATE}?${QueryStr(item)}`;
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

</Userform>


<filesmanagement>


<!--filesmanagement form start -->
                  <div class="card">
                            <div class="card-body">
                                
                                <div class="header-title">               
                                        <!-- search row start -->
										<div class="row">
											<div class="col-12">
												<div class="search-box pull-left">
													<form action="#">
														<input ref="txtSearch" type="text" name="search" placeholder="Search by name..." required>
														<i onclick={OnClickSearch} class="ti-search"></i>
													</form>
												</div>
											</div>
										</div>
										<!-- search row end -->
                                   
                                </div>

                                

                                <div class="single-table mt-3">
                                    <div class="table-responsive">
                                        <table class="table table-hover progress-table text-center">
                                            <thead class="text-uppercase bg-primary">
                                                <tr class="text-white">
                                                	<th scope="col">ID<i  onclick={OnClickOrderID}  class="ti-exchange-vertical ml-2"></i></th>
                                                    <th scope="col">File Name<i  onclick={OnClickOrderFileName}  class="ti-exchange-vertical  ml-2"></i></th>
                                                    <th scope="col">Date <i  onclick={OnClickOrderDate}  class="ti-exchange-vertical ml-2"></i></th>
                                                    <th scope="col">Path <i  onclick={OnClickOrderPath}  class="ti-exchange-vertical ml-2"></i></th>
                                                    <th scope="col">Tag <i  onclick={OnClickOrderTag}  class="ti-exchange-vertical ml-2"></i></th>
                                                    <th scope="col">Status<i  onclick={OnClickOrderStatus}  class="ti-exchange-vertical ml-2"></i></th>
                                                    <th scope="col">Action</th>
                                                </tr>
                                            </thead>
                                            <tbody>
                                                <tr each={item, i in items}>
                                                    <td   onclick={OnClickRowItem} >{item.ID}</td>
                                                    <td   onclick={OnClickRowItem} >{item.FILENAME}</td>
                                                    <td   onclick={OnClickRowItem} >{item.MODIFIEDDATE}</td>
                                                    <td   onclick={OnClickRowItem} >{item.REALFILEPATH}</td>
                                                    <td   onclick={OnClickRowItem} >{item.TAG}</td>
                                                    <td   onclick={OnClickRowItem} > <span class="status-p {item.STATUS?'bg-warning':'bg-primary'}">{item.STATUS?"Active":"Deleted"}</span>  </td>
                                                    <td  onclick={parent.OnClickDeleteRestore} > <i  class="{item.STATUS?'ti-trash':'ti-back-right'}"></i>  </td>
                                                  
                                                </tr>
                                                
                                            </tbody>
                                        </table>
                                        <!-- Pagination start -->
										 <nav aria-label="Page navigation example">
											<ul class="pagination">
												<li class="page-item">
													<a onclick={OnClickPrevPage} class="page-link" href="#" aria-label="Previous">
														<span aria-hidden="true">&laquo;</span>
														<span class="sr-only">Previous</span>
													</a>
												</li>

												<li  each={page in pages}  class="page-item {this.SEARCH.PAGE==page-1?'disabled':''}">
													<a href="#" class="page-link" onclick={OnClickPage}>{page}</a>
												</li>



												<li class="page-item">
													<a onclick={OnClickNextPage} class="page-link" href="#" aria-label="Next">
														<span aria-hidden="true">&raquo;</span>
														<span class="sr-only">Next</span>
													</a>
												</li>
											</ul>
										</nav>
											
										
										<!-- Pagination end -->
                                    </div>
                                </div>
                            </div>
                        </div>
<!-- filesmanagement form end -->
<script>
	var self = this;
		this.APIKEY = this.opts.LOGAPIKEY;  // should get from session
		this.API={
			SEARCH:`api/imagefile/get/${this.APIKEY}`,
			UPDATE:`api/imagefile/update/${this.APIKEY}`,
			TOTALFILES:`api/filestotal/${this.APIKEY}`
		};

		this.SEARCH={
			PAGE:0,
			SIZE:20,
			
			ORDERBY:"",
			DESC:0,

			USERID:'',
			TAG:""
		};
		
		this.pages =[];
		this.items =[];

		this.on('mount', function() {
			console.log("mount");
			this.SEARCH.USERID = localStorage.getItem("SelectedUser");
			this.LoadTotalFiles(this.LoadData);
		})

		 this.on('update', function() {
			console.log("update");
	  	})
		
		LoadTotalFiles(fn)
		{
			var url =`${this.API.TOTALFILES}?${QueryStr(this.SEARCH)}`;
			fetch(url, 
	  		 {
	  		 	method:'get'
	  		 })
			.then(response => response.json())
			.then(jsonData => {
				console.log(jsonData);
				if(jsonData.IsError==false)
				{
					var data = jsonData.Data;
					var totals = 0;
					data.forEach((a)=> totals+=a.FILES);
					var pages =Math.ceil( totals/(this.SEARCH.SIZE?this.SEARCH.SIZE:20) );
					// generation 
					self.pages = [];
					for(i=0;i<pages;i++) self.pages.push(i+1);
				}
				else
					console.error(jsonData.Status);

			})
			.then(r=>
			{
				if(fn) fn();// callback
			})
			.catch(err => {

					console.error(err);
			});
		}
		
	  	LoadData()
	  	{
	  		console.log("Load Data");
	  		var url = `${this.API.SEARCH}?${QueryStr(this.SEARCH)}`;

	  		 fetch(url, 
	  		 {
	  		 	method:'get'
	  		 })
			.then(response => response.json())
			.then(jsonData => {
				console.log(jsonData);
				if(jsonData.IsError==false)
				{
					self.items = jsonData.Data || self.items;
					
					self.update();
				}
				else
					console.error(jsonData.Status);

			})
			.catch(err => {

					console.error(err);
			});
	  	}

		
		OnClickDeleteRestore(event)
		{
			console.log("Click Delete Restore");
			console.log(event.item);
			var item = event.item.item;
			var index = event.item.i;

			item.STATUS=item.STATUS?0:1;
			var obj={ID:item.ID, STATUS: item.STATUS};
		
			
			this.DoUpdate(obj, index);
		}

		DoUpdate(params, index)
		{
			 
			 var url = `${this.API.UPDATE}?${QueryStr(params)}`;

			 fetch(url, 
	  		 {
	  		 	method:'get'
	  		 })
			.then(response => response.json())
			.then(jsonData => {
				console.log(jsonData);
				if(jsonData.IsError==false)
				{
					
					if(jsonData.Data.length>0)
					{
						self.items[index] = jsonData.Data[0];
						self.update();
					}
				}
				else
					console.error(jsonData.Status);

			})
			.catch(err => {

					console.error(err);
			});
		}

		OnClickOrderID()
		{
			this.SEARCH.ORDERBY = "ID";
			this.SEARCH.DESC=this.SEARCH.DESC?0:1;
			this.LoadData();
		}
		OnClickOrderFileName()
		{
			this.SEARCH.ORDERBY = "FILENAME";
			this.SEARCH.DESC=this.SEARCH.DESC?0:1;
			this.LoadData();
		}
		OnClickOrderDate()
		{
			this.SEARCH.ORDERBY = "MODIFIEDDATE";
			this.SEARCH.DESC=this.SEARCH.DESC?0:1;
			this.LoadData();
		}
		
		OnClickOrderPath()
		{
			this.SEARCH.ORDERBY = "REALFILEPATH";
			this.SEARCH.DESC=this.SEARCH.DESC?0:1;
			this.LoadData();
		}
		OnClickOrderTag()
		{
			this.SEARCH.ORDERBY = "TAG";
			this.SEARCH.DESC=this.SEARCH.DESC?0:1;
			this.LoadData();
		}
		OnClickOrderStatus()
		{
			this.SEARCH.ORDERBY = "STATUS";
			this.SEARCH.DESC=this.SEARCH.DESC?0:1;
			this.LoadData();
		}
		

		OnClickSearch()
		{
			var txtSearch = this.refs.txtSearch;
			this.SEARCH.TAG= txtSearch.value;

			this.LoadData();
		}

		
		//--------- pagination
		OnClickPage(event)
		{
			event.preventDefault();

			var item = event.item;
			this.SEARCH.PAGE = item.page-1;
			this.LoadData();
		}

		OnClickRowItem(event)
		{
			
		}
	
</script>
</filesmanagement>




<UserSummary>

	<div class="row"> 
		
		<div class="col-md-4 mt-md-5 mb-3">
			<div class="card">
				<div class="seo-fact sbg2">
					<div class="p-4 d-flex justify-content-between align-items-center">
						<div class="seofct-icon"><i class="ti-share"></i>Downloads</div>
						<h2>{item.Downloads}</h2>
					</div>

				</div>
			</div>
		</div>
		<div class="col-md-4 mt-md-5 mb-3">
			<div class="card">
				<div class="seo-fact sbg3">
					<div class="p-4 d-flex justify-content-between align-items-center">
						<div class="seofct-icon"><i class="ti-files"></i>Total Files</div>
						 <h2>{item.Files}</h2>
															  </div>
				</div>
			</div>
		</div>
		
	</div>
			

	<script>
		var self = this;
		this.APIKEY = this.opts.LOGAPIKEY;  // should get from session
		this.API = `api/summary/${this.APIKEY}`;

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

</UserSummary>


<usersettingform>

	
<div class="card">
                                    <div class="card-body">
                                        <h4 class="header-title">Watermark</h4>

                                        <div class="media">

                                            <img class="img-fluid mr-4" src="assets/images/media/media2.jpg" alt="">
                                            <input type="file" class="custom-file-input" id="inputGroupFile02">
                                            <div class="media-body">

                                                                                    
                                            </div>
                                        </div>
                                    
                                        <h4 class="header-title mt-5">Transformation</h4>
                                        <form>
                                            <fieldset >
                                                <div class="form-group">
                                                    <label for="">Max file size (MB)</label>
                                                    <input type="number" id="" class="form-control" placeholder="0 MB">
                                                </div>
                                                <div class="form-check">
                                                    <input class="form-check-input" type="checkbox" id="disabledFieldsetCheck">
                                                    <label class="form-check-label" for="disabledFieldsetCheck">
                                                        Auto scale down
                                                    </label>
                                                </div>
                                                <div class="form-group">
                                                    <label for="">Extensions</label>
                                                   <input type="text" id="" class="form-control" placeholder="png jpg bmp jpeg">
                                                </div>
                                            </fieldset>
                                        </form>
                                    </div>
                                </div>
                            </div>
		


	<script>
		var self = this;
		this.APIKEY = this.opts.LOGAPIKEY;  // should get from session
		this.API={
			GET:`api/user/get/${this.APIKEY}`,
			UPDATE:`api/user/update/${this.APIKEY}`
		};
		//--------
		this.SEARCH={
			APIKEY: this.opts.ADMINID,
			ISADMIN:1
		};

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
	  		var url=`${this.API.GET}?${QueryStr(this.SEARCH)}`;
	  		 fetch(url, 
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

</usersettingform>



<imagefilesmanagement>


<!--imagefilesmanagement form start -->
	<div class="header-title">               
		<!-- search row start -->
		<div class="row">
			<div class="col-12">
				<div class="search-box pull-left">
					<form action="#">
						<input ref="txtSearch" type="text" name="search" placeholder="Search by name..." required>
						<i onclick={OnClickSearch} class="ti-search"></i>
					</form>
				</div>

				<!-- ordering row start -->
				<div class="btn-group col-lg-4   pull-right" role="group" aria-label="Button group with nested dropdown">
			
					<div class="btn-group" role="group">
						<button type="button" class="btn btn-flat btn-light dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
							Order
						</button>
						<div class="dropdown-menu" aria-labelledby="btnGroupDrop1">
							<a onclick={OnClickOrderDateAsc} class="dropdown-item" href="#">Modified Date Ascending</a>
							<a onclick={OnClickOrderDateDesc} class="dropdown-item" href="#">Modified Date Descending</a>
						</div>
					</div>
				</div>
				<!-- ordering row start -->
			</div>



		</div>
		<!-- search row end -->

	</div>




	<!-- Grid start -->
	<div class="row">
		<div each={item in items}    class="col-lg-3 col-md-5 mt-5">
			<imageblock src={item}></imageblock>
		</div>
	</div>
	<!-- Grid start -->



	<!-- Pagination start -->
	 <nav aria-label="">
		<ul class="pagination mt-3">
			<li class="page-item">
				<a onclick={OnClickPrevPage} class="page-link" href="#" aria-label="Previous">
					<span aria-hidden="true">&laquo;</span>
					<span class="sr-only">Previous</span>
				</a>
			</li>

			<li  each={page in pages}  class="page-item {this.SEARCH.PAGE==page-1?'disabled':''}">
				<a href="#" class="page-link" onclick={OnClickPage}>{page}</a>
			</li>



			<li class="page-item">
				<a onclick={OnClickNextPage} class="page-link" href="#" aria-label="Next">
					<span aria-hidden="true">&raquo;</span>
					<span class="sr-only">Next</span>
				</a>
			</li>
		</ul>
	</nav>
	<!-- Pagination end -->

<!-- imagefilesmanagement form end -->
<script>
	var self = this;
		this.APIKEY = this.opts.LOGAPIKEY;  // should get from session
		this.API={
			SEARCH:`api/imagefile/get/${this.APIKEY}`,
			UPDATE:`api/imagefile/update/${this.APIKEY}`,
			TOTALFILES:`api/filestotal/${this.APIKEY}`
		};

		this.SEARCH={
			PAGE:0,
			SIZE:20,
			
			ORDERBY:"",
			DESC:0,

			USERID:'',
			TAG:""
		};
		
		this.pages =[];
		this.items =[];

		this.on('mount', function() {
			console.log("mount");
			this.SEARCH.USERID = localStorage.getItem("SelectedUser");
			this.LoadTotalFiles(this.LoadData);
		})

		 this.on('update', function() {
			console.log("update");
	  	})
		
		LoadTotalFiles(fn)
		{
			var url =`${this.API.TOTALFILES}?${QueryStr(this.SEARCH)}`;
			fetch(url, 
	  		 {
	  		 	method:'get'
	  		 })
			.then(response => response.json())
			.then(jsonData => {
				console.log(jsonData);
				if(jsonData.IsError==false)
				{
					var data = jsonData.Data;
					var totals = 0;
					data.forEach((a)=> totals+=a.FILES);
					var pages =Math.ceil( totals/(this.SEARCH.SIZE?this.SEARCH.SIZE:20) );
					// generation 
					self.pages = [];
					for(i=0;i<pages;i++) self.pages.push(i+1);
				}
				else
					console.error(jsonData.Status);

			})
			.then(r=>
			{
				if(fn) fn();// callback
			})
			.catch(err => {

					console.error(err);
			});
		}
		
	  	LoadData()
	  	{
	  		console.log("Load Data");
	  		var url = `${this.API.SEARCH}?${QueryStr(this.SEARCH)}`;

	  		 fetch(url, 
	  		 {
	  		 	method:'get'
	  		 })
			.then(response => response.json())
			.then(jsonData => {
				console.log(jsonData);
				if(jsonData.IsError==false)
				{
					self.items = jsonData.Data || self.items;
					
					self.update();
				}
				else
					console.error(jsonData.Status);

			})
			.catch(err => {

					console.error(err);
			});
	  	}

		
		OnClickDeleteRestore(event)
		{
			console.log("Click Delete Restore");
			console.log(event.item);
			var item = event.item.item;
			var index = event.item.i;

			item.STATUS=item.STATUS?0:1;
			var obj={ID:item.ID, STATUS: item.STATUS};
		
			
			this.DoUpdate(obj, index);
		}

		DoUpdate(params, index)
		{
			 
			 var url = `${this.API.UPDATE}?${QueryStr(params)}`;

			 fetch(url, 
	  		 {
	  		 	method:'get'
	  		 })
			.then(response => response.json())
			.then(jsonData => {
				console.log(jsonData);
				if(jsonData.IsError==false)
				{
					
					if(jsonData.Data.length>0)
					{
						self.items[index] = jsonData.Data[0];
						self.update();
					}
				}
				else
					console.error(jsonData.Status);

			})
			.catch(err => {

					console.error(err);
			});
		}

		
		
		OnClickOrderDateAsc()
		{
			this.SEARCH.ORDERBY = "MODIFIEDDATE";
			this.SEARCH.DESC=0;
			this.LoadData();
		}
		OnClickOrderDateDesc()
		{
			this.SEARCH.ORDERBY = "MODIFIEDDATE";
			this.SEARCH.DESC=1;
			this.LoadData();
		}
		
		

		OnClickSearch()
		{
			var txtSearch = this.refs.txtSearch;
			this.SEARCH.TAG= txtSearch.value;

			this.LoadData();
		}

		
		//--------- pagination
		OnClickPage(event)
		{
			event.preventDefault();

			var item = event.item;
			this.SEARCH.PAGE = item.page-1;
			this.LoadData();
		}

		
	
</script>
</imagefilesmanagement>



<imagefilesmanagement2>


<!--imagefilesmanagement2 form start -->
	<div class="header-title">               
		<!-- search row start -->
		<div class="row">
			<div class="col-12">
				<div class="search-box pull-left">
					<form action="#">
						<input ref="txtSearch" type="text" name="search" placeholder="Search by name..." required>
						<i onclick={OnClickSearch} class="ti-search"></i>
					</form>
				</div>

				<!-- ordering row start -->
				<div class="btn-group col-lg-4   pull-right" role="group" aria-label="Button group with nested dropdown">
			
					<div class="btn-group" role="group">
						<button type="button" class="btn btn-flat btn-light dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
							Order
						</button>
						<div class="dropdown-menu" aria-labelledby="btnGroupDrop1">
							<a onclick={OnClickOrderDateAsc} class="dropdown-item" href="#">Modified Date Ascending</a>
							<a onclick={OnClickOrderDateDesc} class="dropdown-item" href="#">Modified Date Descending</a>
							<a onclick={OnClickOrderNameAsc} class="dropdown-item" href="#">Name Ascending</a>
							<a onclick={OnClickOrderNameDesc} class="dropdown-item" href="#">Name Descending</a>
						</div>
					</div>
				</div>
				<!-- ordering row start -->
			</div>



		</div>
		<!-- search row end -->

	</div>


    <!-- upload start -->
    <form class="uploadform" ref="uploadform" draggable="true" action='' method='POST'  enctype='multipart/form-data' target='hidden_iframe' onsubmit={startUpload}>
         
        
        <!-- Grid start -->
        <div class="row">
            <div each={item in items}    class="col-lg-3 col-md-5 mb-5">
                <imageblock src={item}></imageblock>
            </div>
        </div>
        <!-- Grid end -->
        

        <input class="hidencontrol" ref='uploadform_input' type='file' name='filestoupload[]' multiple='' >
        <input class="hidencontrol" ref='uploadform_submit'  type='submit' value='Start Upload'>
		
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
    <!-- Upload end -->



	<!-- Pagination start -->
	 <nav aria-label="">
		<ul class="pagination mt-3">
			<li class="page-item">
				<a onclick={OnClickPrevPage} class="page-link" href="#" aria-label="Previous">
					<span aria-hidden="true">&laquo;</span>
					<span class="sr-only">Previous</span>
				</a>
			</li>

			<li  each={page in pages}  class="page-item {this.SEARCH.PAGE==page-1?'disabled':''}">
				<a href="#" class="page-link" onclick={OnClickPage}>{page}</a>
			</li>



			<li class="page-item">
				<a onclick={OnClickNextPage} class="page-link" href="#" aria-label="Next">
					<span aria-hidden="true">&raquo;</span>
					<span class="sr-only">Next</span>
				</a>
			</li>
		</ul>
	</nav>
	<!-- Pagination end -->

<!-- imagefilesmanagement2 form end -->
  <!-- style -->
  <style scoped>
	.dragover{
		 background-color: #0030df17;
	}
	iframe{
		display:none;

	}
	.uploadform{
		padding:20px;
		min-height:300px;
	}
	.hidencontrol{
		display:none
	}

	imageblock{
		width:310.5px;

	}
	imageblock img
	{
		width:inherit;
	}
  </style>


<script>
        var self = this;
        this.APIKEY = this.opts.LOGAPIKEY;  // should get from session
        this.SESSION = this.opts.SESSION;  // should get from session
		this.API={
			SEARCH:`api/imagefile/get/${this.APIKEY}`,
			UPDATE:`api/imagefile/update/${this.APIKEY}`,
			TOTALFILES:`api/filestotal/${this.APIKEY}`,
           
        
		};

		this.SEARCH={
			PAGE:0,
			SIZE:20,
			
			ORDERBY:"",
			DESC:0,

			USERID:'',
			TAG:""
		};
		
		this.pages =[];
		this.items =[];
        
        
        
        
        

		this.on('mount', function() {
			console.log("mount");
            this.InitUploadForm();
            
			this.SEARCH.USERID = localStorage.getItem("SelectedUser");
			this.LoadTotalFiles(this.LoadData);
		})

		 this.on('update', function() {
			console.log("update");
            this.InitUploadForm();
	  	})
		
		LoadTotalFiles(fn)
		{
			var url =`${this.API.TOTALFILES}?${QueryStr(this.SEARCH)}`;
			fetch(url, 
	  		 {
	  		 	method:'get'
	  		 })
			.then(response => response.json())
			.then(jsonData => {
				console.log(jsonData);
				if(jsonData.IsError==false)
				{
					var data = jsonData.Data;
					var totals = 0;
					data.forEach((a)=> totals+=a.FILES);
					var pages =Math.ceil( totals/(this.SEARCH.SIZE?this.SEARCH.SIZE:20) );
					// generation 
					self.pages = [];
					for(i=0;i<pages;i++) self.pages.push(i+1);
				}
				else
					console.error(jsonData.Status);

			})
			.then(r=>
			{
				if(fn) fn();// callback
			})
			.catch(err => {

					console.error(err);
			});
		}
		
	  	LoadData()
	  	{
	  		console.log("Load Data");
	  		var url = `${this.API.SEARCH}?${QueryStr(this.SEARCH)}`;

	  		 fetch(url, 
	  		 {
	  		 	method:'get'
	  		 })
			.then(response => response.json())
			.then(jsonData => {
				console.log(jsonData);
				if(jsonData.IsError==false)
				{
					self.items = jsonData.Data || self.items;
					
					self.update();
				}
				else
					console.error(jsonData.Status);

			})
			.catch(err => {

					console.error(err);
			});
	  	}

		
		OnClickDeleteRestore(event)
		{
			console.log("Click Delete Restore");
			console.log(event.item);
			var item = event.item.item;
			var index = event.item.i;

			item.STATUS=item.STATUS?0:1;
			var obj={ID:item.ID, STATUS: item.STATUS};
		
			
			this.DoUpdate(obj, index);
		}

		DoUpdate(params, index)
		{
			 
			 var url = `${this.API.UPDATE}?${QueryStr(params)}`;

			 fetch(url, 
	  		 {
	  		 	method:'get'
	  		 })
			.then(response => response.json())
			.then(jsonData => {
				console.log(jsonData);
				if(jsonData.IsError==false)
				{
					
					if(jsonData.Data.length>0)
					{
						self.items[index] = jsonData.Data[0];
						self.update();
					}
				}
				else
					console.error(jsonData.Status);

			})
			.catch(err => {

					console.error(err);
			});
		}

		
		
		OnClickOrderDateAsc()
		{
			this.SEARCH.ORDERBY = "MODIFIEDDATE";
			this.SEARCH.DESC=0;
			this.LoadData();
		}
		OnClickOrderDateDesc()
		{
			this.SEARCH.ORDERBY = "MODIFIEDDATE";
			this.SEARCH.DESC=1;
			this.LoadData();
		}
		OnClickOrderNameAsc()
		{
			this.SEARCH.ORDERBY = "TAG";
			this.SEARCH.DESC=0;
			this.LoadData();
		}
		OnClickOrderNameDesc()
		{
			this.SEARCH.ORDERBY = "TAG";
			this.SEARCH.DESC=1;
			this.LoadData();
		}
		

		OnClickSearch()
		{
			var txtSearch = this.refs.txtSearch;
			this.SEARCH.TAG= txtSearch.value;

			this.LoadData();
		}

		
		//--------- pagination
		OnClickPage(event)
		{
			event.preventDefault();

			var item = event.item;
			this.SEARCH.PAGE = item.page-1;
			this.LoadData();
		}

		
	
//----------------------
        //-- upload section
        this.UPLOADAPI={
            UPLOAD:`upload`,
            PROGRESS:`progress`,
        };
        this.UI={
        	form:null,
        	fileinput:null,
        	submitinput:null
        	
        };
        
       this.uploaddata={uploadid:this.SESSION+Date.now()};
        //----------------------
        
        
        InitUploadForm()
        {
            // on mount
            this.UI.form = $(this.refs.uploadform);
            this.UI.fileinput = $(this.refs.uploadform_input);
            this.UI.submitinput = $(this.refs.uploadform_submit);
            // init events for form drag & drop
            this.refs.uploadform.addEventListener('dragover', this.OnDrag, false);
            this.refs.uploadform.addEventListener('dragleave', this.OnLeave, false);
			this.refs.uploadform.addEventListener('drop', this.OnDrop, false);
        }
        /*
		starting to upload
	*/

    startUpload(e) {
      console.log("start upload");

      this.uploaddata.submittime = Date.now()
        
      var input = e.target[0]
      var form = this.refs.uploadform;

     
      this.uploaddata={
      		uploadid:this.SESSION+Date.now(),
      		APIKEY:this.APIKEY,
      		SESSION:this.SESSION
      	};
      
      form.action =`${this.UPLOADAPI.UPLOAD}?${QueryStr( this.uploaddata)}`;
      
 	  console.log(form.action); // debug

		setTimeout(this.progress(),1000);

      return true;
      
    }
	/*
		call to server for progress of upload
	*/
    progress()
    {
    	 console.log("progress ");
    	var self = this;

    	var url =`${this.UPLOADAPI.PROGRESS}?${QueryStr( this.uploaddata)}`;;
      
    	 fetch(url, {method:'get'})
    	.then(response => response.json())
		.then(jsonData => { 
			console.log(jsonData); 
			if(jsonData<100)
				setTimeout(self.progress(),300);
			else
			{
				this.LoadData();
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
		//console.log(event);

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

		//console.log(event);
    	
    	var droppedFiles = event.dataTransfer.files;

		var uploadinput =this.refs.uploadform_input;
		if(uploadinput)
		{
			uploadinput.files = droppedFiles;
			var btnSubmit = this.refs.uploadform_submit;
			setTimeout(function(){
				$(btnSubmit).trigger("click");
			},500);
			
		}
		
    }
        
</script>
</imagefilesmanagement2>


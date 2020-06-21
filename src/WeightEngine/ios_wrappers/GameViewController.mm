#import <WeightEngine/ios_wrappers/GameViewController.h>

@implementation GameViewController{
  MTKView* _view;
  Weight::Application* app;
}

-(void)viewDidLoad{
  [super viewDidLoad];

  _view=(MTKView*)self.view;
  _view=MTLCreateSystemDefaultDevice();
  _view.backgroundColor=UIColor.blackColor;

  if(!_view.device){
    NSLog(@"Metal is not supported on this device");
    self.view=[[UIView alloc]initWithFrame:self.view.frame];
    return;
  }

  app=Weight::create_application();

  _view.delegate=app.renderer;
}

@end

classdef UiTools
    % Class with static methods for common ui tasks
    methods (Static = true)
        function hTimer = create_timer(timerName,TimerFcn)
            % Create a named timer which will search for previous versions
            % and delete them prior to creation.  Also includes gerneric
            % start and stop callbacks
            %
            % Typical Usage:
            % hTimer = UiTools.create_timer(mfilename,@(src,evt)my_timer_callback);
            % hTimer.Period = 0.05;
            
            hExisting = timerfindall('Name',timerName);
            if ~isempty(hExisting)
                stop(hExisting);
                delete(hExisting);
            end
            
            t = timer;
            t.Name = timerName;
            t.ExecutionMode = 'fixedRate';
            t.TimerFcn = TimerFcn;
            t.StartFcn = @(src,evt)fprintf('Started Timer: %s\tPeriod: %f\n',timerName,t.Period);
            t.StopFcn = @(src,evt)fprintf('Stopped Timer: %s\tPeriod: %f\tAveragePeriod: %f\n',timerName,t.Period,t.AveragePeriod);
            
            hTimer = t;
        end
        function hFigure = create_figure(figureName,figureTag)
            % Usage: hFigure = UiTools.create_figure(figureName,figureTag)
            
            if nargin < 2
                figureTag = strrep(figureName,' ','_');
            end
            
            % Consts
            figureColor = get(0,'defaultUicontrolBackgroundColor');
            
            % Startup
            %Search if the figure exists
            existingFigs = findall(0,'tag',figureTag);
            
            if ~isempty(existingFigs)
                %Figure exists so bring Figure to the focus
                delete(existingFigs)
            end
            
            % Figure Setup
            hFigure = figure(...
                'Units','pixels',...
                'Color',figureColor,...
                'HandleVisibility','callback',...
                'Renderer','OpenGL',...
                'Resize','off',...
                'Menubar','none',...
                'Toolbar','none',...
                'NumberTitle','off',...
                'IntegerHandle','off',...
                'Tag',figureTag,...
                'Name',figureName);
        end
        function save_temp_file(defaultFile,storedVariable)
            %UiTools.save_temp_file(defaultFile,storedVariable)
            % Create a temp file that will be stored in the tempdir
            % directory (e.g. C:\Users\armigrs1\AppData\Local\Temp\)
            %
            % The input "defaultFile" is used as the filename
            
            fullFile = fullfile(tempdir,defaultFile);
            
            try
                fprintf('[%s] Saving temp file "%s"\n',mfilename,fullFile);
                save(fullFile,'storedVariable','-mat');
            catch ME
                msg = { 'Error creating default file', fullFile , ...
                    'Error was: ' ME.message};
                errordlg(msg,'Error setting defaults');
                disp('FAILED');
                disp(storedVariable);
                return
            end
        end
        function storedVariable = load_temp_file(defaultFile)
            % Load temp file from the tempdir
            % directory (e.g. C:\Users\armigrs1\AppData\Local\Temp\)
            %
            % The input "defaultFile" is used as the filename
            
            % Load a mat file in the temp directory
            
            storedVariable = [];
            
            fullFile = fullfile(tempdir,defaultFile);
            if ~exist(fullFile,'file')
                return
            end
            
            try
                S = load(fullFile,'-mat');
            catch ME
                msg = { 'Error reading default file', fullFile , ...
                    'Error was: ' ME.message};
                errordlg(msg,'Error setting defaults');
                return
            end
            
            if isfield(S,'storedVariable')
                storedVariable = S.storedVariable;
            end
        end
        function delete_temp_file(defaultFile)
            % Delete temp file from the tempdir
            % directory (e.g. C:\Users\armigrs1\AppData\Local\Temp\)
            %
            % The input "defaultFile" is used as the filename
            % Load a mat file in the temp directory
            
            fullFile = fullfile(tempdir,defaultFile);
            if exist(fullFile,'file')
                fprintf('[%s] Deleting file "%s"\n',mfilename,fullFile);
                delete(fullFile);
            end
        end
        function fullFilename = ui_select_data_file(extension,prefix)
            % Provides a save dialog with the default file set as the
            % current date and time with extention reflecting contents
            % extension = '.assessmentLog'
            
            if nargin < 2
                %tempFileName = 'defaultFilePrefix';
                %filePrefix = UiTools.load_temp_file(tempFileName);
                filePrefix = UserConfig.getUserConfigVar('userFilePrefix','NEW_USER_');
            else
                filePrefix = prefix;
            end
            
            FilterSpec = ['*' extension];
            DialogTitle = 'Select File to Write';
            DefaultName = [filePrefix datestr(now,'yyyymmdd_HHMMSS') extension];
            [FileName,PathName,FilterIndex] = uiputfile(FilterSpec,DialogTitle,DefaultName);
            
            if FilterIndex == 0
                fullFilename = [];
            else
                fullFilename = fullfile(PathName,FileName);
            end
        end
        function display_error_stack(ME)
            %display_error_stack(ME)
            % Given a Matlab exception, show each individual message in
            % stack and then rethrow error
            fprintf('\n');
            fprintf('---------ERROR--------');
            disp(ME.message);
            for i = 1:length(ME.stack)
                disp(ME.stack(i));
            end
            rethrow(ME);
            
        end
        function sortedDirContents = dir_time_sorted(dirName)
            %sortedDirContents = UiTools.dirTimeSorted(dirName)
            % get directory but reorder by datenum field.  Useful for
            % pulling acquired data in the order acquired
            %
            % 11/2/2012 RSA: Created
            
            % get directory contents from wildcard source
            structDirContents = dir(dirName);
            assert(~isempty(structDirContents),'Input files not found');
            
            % Sort by date
            [~, id] = sort([structDirContents(:).datenum]);
            
            sortedDirContents = structDirContents(id);
            
        end
        
    end
end
